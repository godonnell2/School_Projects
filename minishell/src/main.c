#include "minishell.h"

t_shell    *init_context(void)
{
    t_shell *shell;

    shell = malloc(sizeof(t_shell));
    if (!shell)
    {
        perror("Malloc failed in init_context");
        return (NULL);
    }
    shell->env_vars = NULL;
    shell->env_array = NULL;
    shell->last_exit_code = 0;
    shell->commands = NULL;
    shell->rl_input = NULL;
    shell->state = IDLE;
    return (shell);
}

void    handle_input(t_shell *shell)
{
    t_command   *commands;
    int         ret_code;
    char        **env_array;

    DEBUG_PRINTF("\n--- NEW INPUT CYCLE ---\n");
   
    if (*shell->rl_input == '\0')
    {
        free(shell->rl_input);
        return ;
    }
    add_history(shell->rl_input);
    //PARSER
    commands = NULL;
    ret_code = parser(shell);
    commands = shell->commands;
    if (ret_code == ERR_SYNTAX)
    {
        DEBUG_LOG("syntax error, returning to main loop\n");
        return ;
    }
    else if (shell->commands == NULL)
    {
        DEBUG_LOG("no command to be executed, returning to main loop\n");
        return ;
    }
    if (DEBUG_MODE == 1)
        print_commands(commands); //TEST FUNCTION FOR PARSER
    //EXECUTOR
    env_array = NULL;
    env_array = convert_env_to_array(shell->env_vars);
    if (!env_array)
	{
		DEBUG_LOG( "env_array is NULL\n"); //to be replaced
		exit(1);
	}
    DEBUG_LOG("call resolve comd path in main\n"); 
     
	resolve_all_command_paths(shell, commands);
   
    DEBUG_PRINTF("About to execute pipes:\n");
    execute_pipes(commands, env_array, shell->env_vars, shell); 
    free(shell->rl_input);
    //also free env_array!!
    //free_commands_list(commands);    //free commands list
}

int main(int argc, char **argv, char **envp)
{
    t_shell             *shell;

    g_signal = 0;
    init_signal_handler();
    shell = init_context();
    if (!shell)
        return (1);
    shell->env_vars = get_env_vars(envp);
    // If envp was empty, get_env_vars() may return NULL.
    // Don't treat that as a fatal error—just continue with no vars.
    // if (!shell->env_vars)
    //     return (free(shell), 1);
    (void)argc;
    (void)argv;
    rl_catch_signals = 0;
    while (1) 
    {
        g_signal = 0;
        shell->rl_input = readline("minishell> ");
        if (shell->rl_input == NULL)
        {
            //DEBUG_PRINTF("🛑 readline returned NULL ( exiting...\n");
            write(1, "exit\n", 5);
            break ;
        }
        else if (*shell->rl_input == '\0')
            free(shell->rl_input);
        else
        {
            if (check_for_signals(shell))
                continue ;
            handle_input(shell);
        }
    }
    //free env vars list
    return (0);
}