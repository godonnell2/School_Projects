#include "minishell.h"

//parser just prints result, no execution
//cc -Wall -Wextra -lreadline libft/ft_split.c libft/ft_strjoin.c env_vars_init.c parser_lst.c 

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

t_parser_lst *init_parser_lst(t_env_vars *env_vars)
{
    t_parser_lst *list;

    list = malloc(sizeof(t_parser_lst));
    if (!list)
    {
        perror("malloc failed in init_parser_lst");
        return (NULL);
    }
    list->arg_head = NULL;
    list->arg_tail = NULL;
    list->token_head = NULL;
    list->token_tail = NULL;
    list->chunk_head = NULL;
    list->args_count = 0;
    list->command_head = NULL;
    list->command_tail = NULL;
    list->env_vars = env_vars;
    return (list);
}

//adds a new command to the tail of the command list, sets everything to 0/NULL
t_command *lst_add_new_command(t_parser_lst *list,int args_count)
{
    t_command *node;

    node = malloc(sizeof(t_command));
    if (!node)
    {
        perror("malloc failed in lst_create_command");
        return (NULL);
    }
    ft_memset(node, 0, sizeof(t_command));
    node->args = malloc(sizeof(char *) * (args_count + 1));
    if (!node->args)
    {
        free(node);
        perror("malloc failed in lst_create_command");
        return (NULL);
    }
    ft_memset(node->args, 0, sizeof(char *) * (args_count + 1));
    if (list->command_head == NULL || list->command_tail == NULL)
        list->command_head = node;
    else
        list->command_tail->next = node;
    list->command_tail = node;
    return (node);
}

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
        if (ft_strncmp(current->key, var, len) == 0) //need to replace with libft function
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

char    *expand_env_var(char *ev, int* var_len, t_env_vars *env_vars)
{
    int i;
    char *expanded_var;

    i = 1;
    if (ev[i] == '?')
    {
        i++;
        expanded_var = ft_strdup("0"); //need to fix with last_exit_code once set up
    }
    else if (ft_isalnum(ev[i]) || ev[i] == '_')
    {
        i++;
        while (ft_isalnum(ev[i]) || ev[i] == '_')
            i++;
        expanded_var = ft_strdup(get_env_var(env_vars, ev, i));
    }
    else
    {
        i++;
        expanded_var = ft_substr(ev, 0, 2);
    }
    *var_len = i;
    return (expanded_var);
}

char    *append_ev_value(char *token_str, char *old_expanded_tok, int *i, t_env_vars *env)
{
    char *expanded_tok;
    char *ev_value;
    int var_len;

    var_len = 0;
    ev_value = expand_env_var(&token_str[*i], &var_len, env); //malloc needed
    if (!ev_value)
        return (NULL);
    *i += var_len;
    expanded_tok = ft_strjoin(old_expanded_tok, ev_value);
    free(ev_value);
    return (expanded_tok);
}

char    *expand_all_env_vars(char *token_str, char *expanded_tok, t_env_vars *env)
{
    char *temp;
    int i;
    int start;

    i = 0;
    while (token_str[i])
    {
        temp = expanded_tok;
        if (token_str[i] == '$')//substitute var
            expanded_tok = append_ev_value(token_str, temp, &i, env);
        else//append until var or end
        {
            start = i;
            while (token_str[i] != '$' && token_str[i])
                i++;
            expanded_tok = ft_substr(token_str, start, i);
        }
        free(temp);
        if (!expanded_tok)
        {
            perror("malloc failed in expand_env_vars");
        }
        return (NULL);
    }
    return (expanded_tok);
}

//removes start and end "" and checks for env_vars. If found makes the substitution(s), then returns string.
char *expand_dquotes(t_token *token, t_env_vars *env_vars)
{
    char *token_str;
    char *expanded_token;

    token_str = strdup_len(token->token + 1, token->len - 2); //removes start and end ""
    if (!token_str)
    {
        perror("malloc failed in process_dquotes");
        return (NULL);
    }
    if (!ft_strchr(token_str, '$'))
        return (token_str);
    expanded_token = ft_strdup("");
    if (!expanded_token)
    {
        free(token_str);
        perror("malloc failed in process_dquotes");
        return (NULL);
    }
    expanded_token = expand_all_env_vars(token_str, expanded_token, env_vars);
    if (!expanded_token)
    {
        free(token_str);
        perror("malloc failed in process_dquotes");
    }
    return (expanded_token);
}

char *expand_arg(t_token *token, t_env_vars *env)
{
    char *expanded_tok;

    if (token->type == D_QUOTES)
        expanded_tok = expand_dquotes(token, env);
    else if (token->type == S_QUOTES)
        expanded_tok = strdup_len(token->token + 1, token->len - 2);
    else
        expanded_tok = strdup_len(token->token, token->len);
    if (!expanded_tok)
        return (NULL);
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
    arg = expand_arg(token, list->env_vars);
    if (!arg)
        return (NULL);
    token = token->next;
    while (token && is_arg_tok(token->type) && token->prev_white_space == 0)
    {
        concat1 = arg;
        concat2 = expand_arg(token, list->env_vars);
        if (!concat2)
            return (free(arg), NULL);
        arg = ft_strjoin(concat1, concat2);
        free(concat1);
        free(concat2);
        if (!arg)
            return (NULL);
        token = token->next;
    }
    return (arg);
}

void    add_redirection_arg(char *arg, t_command *command_table, t_tok_type target_field)
{
    if (target_field == REDIR_IN)
        command_table->infile = arg;
    else if (target_field == REDIR_OUT || target_field == APPEND_OUT)
    {
        command_table->outfile = arg;
        if (target_field == APPEND_OUT)
            command_table->append_out = 1;
    }
    else if (target_field == HEREDOC)
        command_table->heredoc_eof = arg;
}

void    print_syntax_error(t_tok_type type)
{
    if (type == PIPE)
        perror("syntax error near unexpected token `|'");
    else if (type == REDIR_IN)
        perror("syntax error near unexpected token `<'");
    else if (type == REDIR_OUT || type == APPEND_OUT)
        perror("syntax error near unexpected token `>'");
    else if (type == HEREDOC)
        perror("syntax error near unexpected token `<<'");
    else
        perror("syntax error");
}

t_parser_lst   *add_arg_to_list(t_parser_lst *list_params, char *arg)
{
    t_arg    *node;

    node = malloc(sizeof(t_token));
    if (!node)
    {
        perror("malloc failed in add_arg_to_list");
        return (NULL);
    }
    node->arg = arg;
    node->next = NULL;
    if (list_params->arg_head || list_params->arg_tail == NULL)
        list_params->arg_head = node;
    else
        list_params->arg_tail->next = node;
    list_params->arg_tail = node;
    return (list_params);
}

char **lst_args_to_array(t_arg *arg_head, int args_total)
{
    char    **args;
    t_arg   *current_node;
    int     i;

    current_node = arg_head;
    args = malloc(sizeof(char *) * (args_total + 1));
    if (!args)
    {
        perror("malloc failed in lst_args_to_array");
        return (NULL);
    }
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

t_token *process_tokens_in_chunk(t_command *command_table, t_parser_lst *list)
{
    t_token     *token;
    char        *arg;
    char        *concat1;
    char        *concat2;
    t_tok_type  table_target;
    int         args_total;

    concat1 = NULL;
    concat2 = NULL;
    args_total = 0;
    token = list->chunk_head;
    //check how to implement error checking for operators
    while (token != NULL && token->type != PIPE)
    {
        printf("new token being processed: %s\n", token->token);
        table_target = ARGS;
        arg = NULL;
        if (is_operator_tok(token->type))
        {
            printf("operator tok\n");
            table_target = token->type;
            token = token->next;
            if (is_operator_tok(token->type))
            {
                print_syntax_error(token->type);
                return (NULL);
            }
        }
        if (token && is_arg_tok(token->type))
        {
            printf("arg tok\n");
            arg = process_arg_tok(token, list);
            if (arg == NULL)
                return (NULL);
            token = token->next;
            while (token && token->prev_white_space == 0 && is_arg_tok(token->type))
                token = token->next;
            if (table_target == ARGS)
            {
                list = add_arg_to_list(list, arg);
                if (!list)
                    return (free(arg), NULL);
            }
            else
                add_redirection_arg(arg, command_table, table_target);
            args_total++;
        }
    }
    command_table->args = lst_args_to_array(list->arg_head, args_total);
    if (!command_table->args)
        return (NULL);
    return (list->token_tail); //need to ensure it is the tail???
}

//adds tokens found in chunk to the command table
//t_command    *add_command(t_token *token, t_command *head, t_command **prev_command, int args_count)
t_command    *add_command(t_parser_lst *list)
{
    t_command   *command_table;
    t_token     *current_token;
    int         total_args;

    current_token = list->token_tail;
    total_args = list->args_count;
    if (current_token == NULL) //to work out if this is the right test now
    {
        perror("syntax error near unexpected token `|'");
        exit (1); //TODO free everything and return prompt
    }
    if (current_token->type == PIPE)
        current_token = current_token->next;
    command_table = lst_add_new_command(list, list->args_count); //adds empty command table to end of list
    if (!command_table)
        return (NULL); //TODO free everything and return prompt
    current_token = process_tokens_in_chunk(command_table, list);
    if (list->args_count > 0)
        perror("args count not zero");//temp to check
    list->args_count = 0;
    list->chunk_head = current_token;
    if (current_token != list->token_tail)
        printf("debug in add_command: new chunk head is not at tail\n"); //temp
    return (list->command_head);
}

t_parser_lst	*lst_add_new_token(t_parser_lst *list_params)//rename node
{
    t_token    *node;

    node = malloc(sizeof(t_token));
    if (!node)
    {
        perror("malloc failed in lst_add_new_token");
        return (NULL);
    }
    node->token = NULL;
    node->len = 0;
    node->type = 0;
    node->next = NULL;
    if (list_params->token_head == NULL || list_params->token_tail == NULL)
    {
        list_params->token_head = node;
        list_params->chunk_head = node;
    }
    else
        list_params->token_tail->next = node;
    list_params->token_tail = node;
    return (list_params);
}

void    record_token_info(t_token *token, char *str, int len, int type)
{
    token->token = str;
    token->len = len;
    token->type = type;
}

char    *tok_quotes(t_parser_lst *list_params, char *command, char quote)
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
    if (*command == quote)
    {
        token->len++;
        command++;
    }
    list_params->args_count++;
    return (command);
}

char    *tok_redirect(t_parser_lst *list_params, char *command)
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

char    *tok_args(t_parser_lst *list_params, char *command)
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
    list_params->args_count++;
    return (command);
}

char    *tokenizer(t_parser_lst *list_params, char *command)
{
    t_token     *token;

    token = list_params->token_tail;
    if (*command == ' ')
        token->prev_white_space = 1;
    while (*command == ' ')
        command++;
    if (*command == '"')
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
    return (command);
}

void print_tokens(t_token *head)
{
    t_token *token;

    token = head;
    write(1, "\nTokens: ", 9);
    while (token)
    {
        write(1, "{", 1);
        write(1, token->token, token->len);
        write(1, "} ", 2);
        token = token->next;
    }
    write(1, "\n\n", 2);
}

t_command    *parser(char *command, t_command *commands_head, t_env_vars *env_vars)
{
    t_parser_lst   *list;
    int i;
    int args_count;

    //tokenizer
    list = init_parser_lst(env_vars);
    if (list == NULL)
    {
        perror("malloc failed in parse_commands");
        return (NULL);
    }
    i = 0;
    args_count = 0;
    while (*command)
    {
        list = lst_add_new_token(list); //add empty token to list NODE
        if (list == NULL)
        {
            return (NULL);//free everything and return prompt
        }        
        command = tokenizer(list, &command[i]); //record token info
        if (list->token_tail->type == PIPE) //populate the command table and prepare for new chunk
        {
            list->command_head = add_command(list);
        }
    }
    commands_head = add_command(list);
    print_tokens(list->token_head);
    //free tokens
    free(list);
    return (commands_head);
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

void    handle_input(char *input, t_env_vars *env_vars)
{
    t_command   *commands;
    int i;
    int j;

    add_history(input);
    //handle input here
    if (!strcmp(input, "env")) //need to trim any spaces so prob better to tokenize as usual and process in executor
    {
        print_env_vars(env_vars);
        return ;
    }
    commands = NULL;
    //tokenize input and parse to commands table
    commands = parser(input, commands, env_vars);
    i = 0;
    //print commands table
    while (commands != NULL)
    {
        j = 0;
        printf("commands[%i]\n", i);
        if (commands->heredoc_eof)
            printf("heredoc eof: %s\n", commands->heredoc_eof);
        if (commands->append_out)
            printf("append out: %s\n", commands->outfile);
        if (commands->infile)
            printf("infile: %s\n", commands->infile);
        if (commands->outfile)
            printf("outfile: %s\n", commands->outfile);
        while (commands->args[j])
        {
            printf("args[%i]: %s\n", j, commands->args[j]);
            j++;
        }
        printf("\n");
        i++;
        commands = commands->next;
    }
    free(input);
    //execute_commands
/*             if (commands_index == 0)
        execute_command(commands->args, envp);
    else
        execute_pipes(commands, commands_index + 1, envp); */
    //clear_table_buffer(&commands[0], &commands_index);
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
            printf("\n");
            break;
        }
        else if (strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        else
        {
            handle_input(input, env_vars);
        }
    }
    return (0);
}