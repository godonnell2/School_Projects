#include "minishell.h"

//updates node with ptr to token start in original input str, length and type
static void    record_token_info(t_token *token, char *str, int len, int type)
{
    token->token = str;
    token->len = len;
    token->type = type;
}

//records token info for dquotes and squotes
static char    *tok_quotes(t_parser_lst *list_params, char *command, char quote)
{
    t_token     *token;

    token = list_params->token_tail;
    if (quote == '"')
        record_token_info(token, command, 1, D_QUOTES);
    else
        record_token_info(token, command, 1, S_QUOTES);
    command++;
    while (*command != quote && *command)
    {
        token->len++;
        command++;
    }
    if (*command != quote)
    {
        print_syntax_error(END);
        return (NULL);
    }
    else
    {
        token->len++;
        command++;
    }
    return (command);
}

//records token info for redirects
static char    *tok_redirect(t_parser_lst *list_params, char *command)
{
    t_token     *token;
    int i;

    token = list_params->token_tail;
    i = 0;
    if (command[i] == '<' && command[i + 1] == '<')
    {
        record_token_info(token, &command[i], 2, HEREDOC);
        i++;
    }
    else if (command[i] == '<')
        record_token_info(token, &command[i], 1, REDIR_IN);
    else if (command[i] == '>' && command[i + 1] == '>')
    {
        record_token_info(token, &command[i], 2, APPEND_OUT);
        i++;
    }
    else if (command[i] == '>')
        record_token_info(token, &command[i], 1, REDIR_OUT);
    i++;
    return (&command[i]);
}
//records token info for args
static char    *tok_args(t_parser_lst *list_params, char *command)
{
    t_token     *token;

    token = list_params->token_tail;
    record_token_info(token, command, 0, ARGS);
    while (*command && *command != ' ' && !is_pipe(*command) 
        && !is_redirect(*command) && *command != '"' && *command != '\'')
    {
        token->len++;
        command++;
    }
    return (command);
}

//checks token and records details; returns ptr to the next token
int    tokenizer(t_parser_lst *list_params, char **command_str_ptr)
{
    t_token     *token;
    char        *command;

    command = *command_str_ptr;
    token = list_params->token_tail;
    if (*command == ' ')
        token->prev_white_space = 1;
    while (*command == ' ')
        command++;
    if (*command == '\0')
        record_token_info(token, command, 1, END);
    else if (*command == '"')
        command = tok_quotes(list_params, command, '"');
    else if (*command == '\'')
        command = tok_quotes(list_params, command, '\'');
    else if (is_redirect(*command))
        command = tok_redirect(list_params, command);
    else if (!is_pipe(*command))
        command = tok_args(list_params, command);
    else
    {
        record_token_info(token, command, 1, PIPE);
        command++;
    }
    if (command == NULL)
        return (ERR_SYNTAX);
    *command_str_ptr = command;
    return (OK);
}
