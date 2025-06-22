#include "minishell.h"

int is_operator_tok(t_tok_type type)
{
    return (type == REDIR_IN || type == REDIR_OUT || type == APPEND_OUT
            || type == HEREDOC || type == PIPE);
}

int is_arg_tok(t_tok_type type)
{
    return (type == ARGS || type == D_QUOTES || type == S_QUOTES);
}

int is_redirect(char c)
{
    return (c == '>' || c == '<');
}

int is_pipe(char c)
{
    return (c == '|');
}

char *strdup_len(char *str, int len)
{
    char *dst;
    int i;

    dst = malloc(sizeof(char) * (len + 1));
    if (dst == NULL)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dst[i] = str[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}