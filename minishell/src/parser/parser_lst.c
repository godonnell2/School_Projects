#include "minishell.h"

char *heredoc_var_expansion(char *line, t_parser_lst *list)
{
    char *expanded_heredoc;

    expanded_heredoc = ft_strdup("");
    if (!expanded_heredoc)
    {
        perror("malloc failed in expand_arg");
        return (free(line), NULL);
    }
    expanded_heredoc = expand_env_vars(line, expanded_heredoc, HEREDOC_INPUT, list);
    free(line);
    if (!expanded_heredoc)
        perror("malloc failed in expand_arg");
    return (expanded_heredoc);
}

int	get_heredoc(const char *delimiter, t_redirect *redir_node, t_parser_lst *list)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
        if (redir_node->heredoc_quoted == 0 && ft_strchr(line, '$')) //these 2 lines are the only thing changed from Grace version
            line = heredoc_var_expansion(line, list); //plus the extra function params needed for var expansion
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void    add_redirection_arg(char *arg, t_command *command_table, t_parser_lst *list)
{
    t_redirect *redir_node;

    redir_node = lst_add_new_redirect(command_table, list->target_field);
    if (redir_node == NULL)
    {
        free(arg);
        error_free_and_exit(list, "malloc failed in add_redirection_arg");
    }
    redir_node->target = arg;
    redir_node->type = list->target_field;
    if (list->target_field == HEREDOC)
    {
        redir_node->heredoc_quoted = list->heredoc_quoted;
        redir_node->heredoc_fd = get_heredoc(redir_node->target, redir_node, list);
        if (redir_node->heredoc_fd == -1)
            DEBUG_PRINTF("Heredoc write error in add_redirection_arg\n"); // any error messages needed?????
    }
}

int validate_syntax(t_token **token)
{
    t_token *next_token;

    next_token = (*token)->next;
    if (!next_token || next_token->type == END) //handles redirections without arg
    {
        print_syntax_error(END);
    }
    else if (is_operator_tok(next_token->type))
    {
        print_syntax_error((*token)->next->type);
    }
    else
    {
        *token = next_token;
        return (OK);
    }
    return (ERR_SYNTAX);
}

int process_tokens_in_chunk(t_command *command_table, t_parser_lst *list, int *args_total)
{
    t_token     *token;
    char        *arg;

    token = list->chunk_head;
    while (token != NULL && token->type != PIPE && token->type != END)
    {
        list->target_field = token->type;
        arg = NULL;
        if (is_operator_tok(token->type))
        {
            if (validate_syntax(&token) == ERR_SYNTAX)
                return (ERR_SYNTAX);
        }
        if (token && is_arg_tok(token->type))
        {
            arg = process_arg_tok(token, list);
            if (arg == NULL)    
                error_free_and_exit(list, "malloc failed in process_arg_tok");
            token = list->current_token;
            if (*arg == '\0' && list->shell->last_exit_code == 139)
            {
                free(arg);
                list->shell->last_exit_code = 0;
            }
            else if (is_arg_tok(list->target_field))
            {
                add_arg_to_list(list, arg); // malloc exit inside
                *args_total += 1;
            }
            else
            {
                add_redirection_arg(arg, command_table, list);
                //*args_total += 1;
            }
            list->heredoc_quoted = 0;
        }
    }
    return (OK);
}

char **lst_args_to_array(t_parser_lst *list, int args_total)
{
    char    **args;
    t_arg   *current_node;
    int     i;

    current_node = list->arg_head;
    args = malloc(sizeof(char *) * (args_total + 1));
    if (!args)
        error_free_and_exit(list, "malloc failed in lst_args_to_array");
    i = 0;
    while (current_node && i < args_total)
    {
        args[i] = current_node->arg;
        current_node = current_node->next;
        i++;
    }
    args[i] = NULL;
    return (args);
}

t_token *skip_pipe_validate_syntax(t_parser_lst *list)
{
    t_token *token;

    token = list->chunk_head;
    if (token->type != PIPE) //first command
        return (token);
    else if (!token->next || list->token_head == token || token->next->type == PIPE)
    {//handles pipe at end (incomplete) /pipe at start / double pipes
        print_syntax_error(PIPE);
        return (NULL);
    }
    return (token->next);
}

//adds tokens found in chunk to the command table
int    add_command(t_parser_lst *list)
{
    t_command   *new_command;
    int         args_total;
    int         ret_code;

    ret_code = 0;
    args_total = 0;
    new_command = lst_add_new_command(list); //adds empty command table to end of list. malloc exit inside
    list->chunk_head = skip_pipe_validate_syntax(list);
    if (list->chunk_head == NULL)
        return (ERR_SYNTAX);
    ret_code = process_tokens_in_chunk(new_command, list, &args_total);
    if (ret_code == ERR_SYNTAX)
        return (ERR_SYNTAX);
    else if (list->arg_head)
        new_command->args = lst_args_to_array(list, args_total);
    list->chunk_head = list->token_tail;
    free_args_list(list);
    if (new_command->args == NULL && new_command->redirs == NULL)
    {
        DEBUG_LOG("EMPTY COMMAND DETECTED - removing from list");
        lst_remove_last_command(list, new_command);
        ret_code = ERR_OTHER;
    }
    return (ret_code);
}

int  parse_command_str(char *command, t_parser_lst *list)
{
    int            ret_code;

    while (*command)
    {
        ret_code = OK;
        if (lst_add_empty_token_node(list) == ERR_MALLOC) //add empty token to list NODE
            error_free_and_exit(list, "malloc failed in lst_add_token_node");     
        ret_code = tokenizer(list, &command); //traverse token and record info
        if (ret_code == ERR_SYNTAX)
            return (ERR_SYNTAX);
        if (list->token_tail->type == PIPE) //populate the command table and prepare for new chunk
        {
            //print_tokens(list->token_head);
            ret_code = add_command(list);
            if (ret_code == ERR_SYNTAX)
                return (ERR_SYNTAX);
        }
    }
    if (list->token_head->type == END) //handles input of only spaces
        return (ERR_SYNTAX);
    ret_code = add_command(list);
    if (ret_code == ERR_SYNTAX)
        return (ERR_SYNTAX);
    list->shell->commands = list->command_head;
    if (DEBUG_MODE == 1)
        print_tokens(list->token_head); // for testing
    free_tokens_list(list);
    free(list);
    return (ret_code);
}

int parser(t_shell *shell)
{
    t_parser_lst   *list_params;
    int            ret_code;
    char           *command;

    ret_code = 0;
    command = shell->rl_input;
    list_params = init_parser_lst(shell->env_vars, shell->rl_input, shell);
    if (list_params == NULL)
        error_free_and_exit(list_params, "malloc failed in init_parser_lst");
    ret_code = parse_command_str(command, list_params);
    if (ret_code == ERR_SYNTAX)
    {
        syntax_error_free_parser_lst(list_params);
        shell->last_exit_code = 2;
        return (ERR_SYNTAX);
    }
    return (OK);
}

 void print_env_vars(t_env_vars *env_vars)
{
    t_env_vars *current;

    current = env_vars;
    while (current != NULL)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
} 

// void    handle_input(char *input, t_env_vars *env_vars)
// {
//     t_command   *commands;

//     if (*input == '\0')
//     {
//         free(input);
//         return ;
//     }
//     add_history(input);
//     if (!strcmp(input, "env")) //need to trim any spaces so prob better to tokenize as usual and process in executor
//     {
//         print_env_vars(env_vars);
//         return ;
//     }
//     commands = NULL;
//     //tokenize input and parse to commands table
//     commands = parser(input, commands, env_vars);
//     if (commands == NULL)
//     {
//         free(input);
//         return ;
//     }
//     //print commands table
//     print_commands(commands);
//     free(input);
//     //execute_commands
//     free_commands_list(commands);
// }

// int main(int argc, char **argv, char **envp)
// {
//     char    *input;
//     t_env_vars *env_vars;

//     env_vars = get_env_vars(envp);
//     (void)argc;
//     (void)argv;
//     while (1) 
//     {
//         input = readline("minishell> ");
//         if (input == NULL)
//         {
//             printf("exit\n");
//             break;
//         }
//         else if (*input == '\0')
//             free(input);
//         else if (strcmp(input, "exit") == 0)
//         {
//             free(input);
//             break;
//         }
//         else
//         {
//             handle_input(input, env_vars);
//         }
//     }
//     return (0);
// }
