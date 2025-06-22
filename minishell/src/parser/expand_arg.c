#include "minishell.h"

/* //removes start and end "" and checks for env_vars. If found makes the substitution(s), then returns string.
char *expand_dquotes(t_token *token, t_parser_lst *list)
{
    char *token_str;
    char *expanded_token;

    token_str = strdup_len(token->token + 1, token->len - 2); //removes start and end ""
    if (!token_str)
        return (NULL);
    if (!ft_strchr(token_str, '$'))
        return (token_str);
    expanded_token = ft_strdup("");
    if (!expanded_token)
    {
        free(token_str);
        return (NULL);
    }
    expanded_token = expand_all_env_vars(token_str, expanded_token, list);
    free(token_str);
    return (expanded_token);
} */

char *expand_arg(t_token *token, t_parser_lst *list)
{
    char *token_str;
    char *expanded_tok;

    if(token->type == D_QUOTES || token->type == S_QUOTES)
    {
        token_str = strdup_len(token->token + 1, token->len - 2);
        if (list->target_field == HEREDOC)
            list->heredoc_quoted = 1;
    }
    else
        token_str = strdup_len(token->token, token->len);
    if (!token_str)
    {
        perror("malloc failed in expand_arg");
        return (NULL);
    }
    if (token->type == S_QUOTES || list->target_field == HEREDOC || !ft_strchr(token_str, '$')) //no env var to expand
        return (token_str);
    expanded_tok = ft_strdup("");
    if (!expanded_tok)
    {
        perror("malloc failed in expand_arg");
        return (free(token_str), NULL);
    }
    expanded_tok = expand_env_vars(token_str, expanded_tok, token->type, list);
    free(token_str);
    if (!expanded_tok)
        perror("malloc failed in expand_arg");
    return (expanded_tok);
}

//process arg tok then check for concatenation needs
char   *process_arg_tok(t_token *token, t_parser_lst *list)
{
    char        *arg;
    char        *concat1;
    char        *concat2;

    concat1 = NULL;
    concat2 = NULL;
    arg = expand_arg(token, list);
    if (!arg)
        return (NULL);
    else if (*arg == '\0' && token->type != D_QUOTES) // && !(list->chunk_head == token && (token->next == NULL || token->next->type == PIPE || token->next->type == END))
    {
        //if single arg not expanded and it is the only one in the chunk
        DEBUG_LOG("lone empty string detected - skipping");
        list->shell->last_exit_code = 139;
        list->current_token = token->next;
        return (arg);
    }
    token = token->next;
    while (token && is_arg_tok(token->type) && token->prev_white_space == 0)
    {
        concat1 = arg;
        concat2 = expand_arg(token, list);
        if (!concat2)
            return (free(arg), NULL);
        arg = ft_strjoin(concat1, concat2);
        free(concat1);
        free(concat2);
        if (!arg)
            return (NULL);
        token = token->next;
    }
    list->current_token = token;
    return (arg);
}
