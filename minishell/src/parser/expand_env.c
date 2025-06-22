#include "minishell.h"

const char *get_env_var(t_env_vars *env_vars, const char *var, int len)
{
    t_env_vars *current;

    if (*var == '$')
    {
        var++;
        len--;
    }
    if (len == 0)
        return (NULL);
    current = env_vars;
    while (current)
    {
        if (strncmp(current->key, var, len) == 0 && current->key[len] == '\0') //need to replace with libft function
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

char    *expand_env_var(char *ev, int* var_len, t_parser_lst *list)
{
    int i;
    const char *env_var;
    char *expanded_var;

    i = 1;
    if (ev[i] == '?')
    {
        i++;
        expanded_var = ft_itoa(list->shell->last_exit_code);
    }
    else if (ft_isalnum(ev[i]) || ev[i] == '_')
    {
        i++;
        while (ft_isalnum(ev[i]) || ev[i] == '_')
            i++;
        env_var = get_env_var(list->env_vars, ev, i);
        if (!env_var)
            expanded_var = ft_strdup("");
        else
            expanded_var = ft_strdup(env_var);
    }
    else
    {
        i++;
        expanded_var = ft_substr(ev, 0, 2);
    }
    *var_len = i;
    return (expanded_var);
}

char    *append_ev_value(char *token_str, char *old_expanded_tok, int *i, t_parser_lst *list)
{
    char *expanded_tok;
    char *ev_value;
    int var_len;

    var_len = 0;
    ev_value = expand_env_var(&token_str[*i], &var_len, list); //malloc needed
    if (!ev_value)
        return (NULL);
    *i += var_len;
    expanded_tok = ft_strjoin(old_expanded_tok, ev_value);
    free(ev_value);
    return (expanded_tok);
}

/* char    *expand_all_env_vars(char *token_str, char *expanded_tok, t_parser_lst *list)
{
    char *temp;
    char *literal;
    int i;
    int start;

    i = 0;
    while (token_str[i])
    {
        temp = expanded_tok;
        if (token_str[i] == '$')//substitute var
            expanded_tok = append_ev_value(token_str, temp, &i, list);
        else//append until var or end
        {
            start = i;
            while (token_str[i] != '$' && token_str[i])
                i++;
            literal = ft_substr(token_str, start, i - start);
            expanded_tok = ft_strjoin(expanded_tok, literal);
            free(literal);
        }
        free(temp);
        if (!expanded_tok)
            return (NULL);
    }
    return (expanded_tok);
} */

int    is_valid_char(char c, t_tok_type type)
{
    if (type == D_QUOTES || type == HEREDOC_INPUT)
        return (c != '\0');
    else
        return (c != ' ' && c != '\t' && c != '\0');
}

char    *expand_env_vars(char *token_str, char *expanded_tok, t_tok_type type, t_parser_lst *list)
{
    char *temp;
    char *literal;
    int i;
    int start;

    i = 0;
    while (is_valid_char(token_str[i], type))
    {
        temp = expanded_tok;
        if (token_str[i] == '$')//substitute var
            expanded_tok = append_ev_value(token_str, temp, &i, list);
        else//append until var or end
        {
            start = i;
            while (token_str[i] != '$' && is_valid_char(token_str[i], type))
                i++;
            literal = ft_substr(token_str, start, i - start);
            expanded_tok = ft_strjoin(expanded_tok, literal);
            free(literal);
        }
        free(temp);
        if (!expanded_tok)
            return (NULL);
    }
    return (expanded_tok);
}
