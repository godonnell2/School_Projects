#include "minishell.h"

void    error_free_and_exit(t_parser_lst *list, const char *error_message)
{
    if (error_message)
        perror(error_message);
    free_args_list(list);
    free_tokens_list(list);
    free_commands_list(list->command_head);
    free_env_vars(list->env_vars);
    free(list->readline_command);
    free(list);
    DEBUG_LOG("freed rl command and parser list\n");
    exit (1);
}

void    syntax_error_free_parser_lst(t_parser_lst *list)
{
    free_args_list(list);
    free_tokens_list(list);
    free_commands_list(list->command_head);
    free(list->readline_command);
    free(list);
    DEBUG_LOG("freed rl command and parser list\n");
}

void    print_syntax_error(t_tok_type type)
{
    if (type == PIPE)
        ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
    else if (type == REDIR_IN)
        ft_putstr_fd(" syntax error near unexpected token `<'\n", 2);
    else if (type == REDIR_OUT)
        ft_putstr_fd(" syntax error near unexpected token `>'\n", 2);
    else if (type == APPEND_OUT)
        ft_putstr_fd(" syntax error near unexpected token `>>'\n", 2);
    else if (type == HEREDOC)
        ft_putstr_fd(" syntax error near unexpected token `<<'\n", 2);
    else if (type == END)
        ft_putstr_fd(" syntax error near unexpected token `newline'\n", 2);
    else
        perror(" syntax error");
}