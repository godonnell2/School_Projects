#include "minishell.h"

void    handle_input(char *input, t_env_vars *env_vars)
{
    t_command   *commands;
    char        **env_array;

    //temp for num commands
	//int num_commands = 2;shouldnt need this 
     printf("\n--- NEW INPUT CYCLE ---\n");
    if (*input == '\0')
    {
        free(input);
        return ;
    }
    add_history(input);
    //PARSER
    commands = NULL;
    commands = parser(input, commands, env_vars);
    if (commands == NULL)
    {
        free(input);
        return ;
    }
    print_commands(commands); //TEST FUNCTION FOR PARSER
    //EXECUTOR
    env_array = NULL;
    env_array = convert_env_to_array(env_vars);
    if (!env_array)
	{
		fprintf(stderr, "env_array is NULL\n"); //to be replaced
		exit(1);
	}
	resolve_all_command_paths(env_vars, commands);
    printf("About to execute pipes:\n");
    execute_pipes(commands, env_array, env_vars);
   
    free(input);
    //also free env_array!!
    free_commands_list(commands);    //free commands list
}

int main(int argc, char **argv, char **envp)
{
    char    *input;
    t_env_vars *env_vars;

    env_vars = get_env_vars(envp);
    (void)argc;
    (void)argv;
    while (1) 
    {
        input = readline("minishell> ");
        if (input == NULL)
        {
           printf("🛑 readline returned NULL ( exiting...\n");
            break;
        }
        else if (*input == '\0')
            free(input);
        else if (strcmp(input, "exit") == 0)
        {
            free(input);
           //break; //THIS IS NOW HANDLED BY THE BUILTIN EXIT dont want to break loop or it exits early 
        }
        else
        {
            handle_input(input, env_vars);
        }
    }
    //free env vars list
    return (0);
}