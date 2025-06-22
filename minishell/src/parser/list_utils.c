#include "minishell.h"

//creates the t_parser_lst master struct
t_parser_lst *init_parser_lst(t_env_vars *env_vars, char *command, t_shell *shell)
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
    list->current_token = NULL;
    list->command_head = NULL;
    list->command_tail = NULL;
    list->env_vars = env_vars;
    list->readline_command = command;
    list->shell = shell;
    list->target_field = 0;
    list->heredoc_quoted = 0;
    return (list);
}

//creates a new empty t_token node and adds to back of list
int lst_add_empty_token_node(t_parser_lst *list)
{
    t_token    *node;

    node = malloc(sizeof(t_token));
    if (!node)
        error_free_and_exit(list, "malloc failed in lst_add_empty_token_node");
    node->token = NULL;
    node->len = 0;
    node->type = 0;
    node->prev_white_space = 0;
    node->next = NULL;
    if (list->token_head == NULL || list->token_tail == NULL)
    {
        list->token_head = node;
        list->chunk_head = node;
    }
    else
        list->token_tail->next = node;
    list->token_tail = node;
    return (OK);
}

//creates a new empty t_command node and adds to back of commands list
t_command *lst_add_new_command(t_parser_lst *list)
{
    t_command *node;

    node = malloc(sizeof(t_command));
    if (!node)
        error_free_and_exit(list, "malloc failed in lst_add_new_command");
    ft_memset(node, 0, sizeof(t_command));
    if (list->command_head == NULL || list->command_tail == NULL)
        list->command_head = node;
    else
        list->command_tail->next = node;
    list->command_tail = node;
    return (node);
}

//creates a new empty t_command node and adds to back of commands list
void    lst_remove_last_command(t_parser_lst *list, t_command *command)
{
    t_command *node;

    if (list->command_head == command)
        list->command_head = NULL;
    else //remove node from list
    {
        node = list->command_head;
        while(node->next != command)
            node = node->next;
        node->next = NULL;
        list->command_tail = node;
    }
    free_command(command);
    DEBUG_LOG("removed last command from list\n");
    return ;
}

//creates a new t_redirect node to the back of the redirects list
t_redirect *lst_add_new_redirect(t_command *command, t_tok_type type)
{
    t_redirect *new_node;
    t_redirect *list_node;

    new_node = malloc(sizeof(t_redirect));
    if (!new_node)
        return (NULL);
    ft_memset(new_node, 0, sizeof(t_redirect));
    if (command->redirs == NULL)
        command->redirs = new_node;
    else
    {
        list_node = command->redirs;
        while (list_node->next)
            list_node = list_node->next;
        list_node->next = new_node;
    }
    return (new_node);
}

/* //creates a new empty t_command node and adds to back of commands list
t_redirect *lst_add_new_redirect(t_command *command, t_tok_type type)
{
    t_redirect *new_node;
    t_redirect **list_node;

    new_node = malloc(sizeof(t_redirect));
    if (!new_node)
        return (NULL);
    ft_memset(new_node, 0, sizeof(t_redirect));
    if (type == HEREDOC || type == REDIR_IN)
        list_node = &command->redir_in;
    else if (type == REDIR_OUT || type == APPEND_OUT)
        list_node = &command->redir_out;
    else
    {
        DEBUG_PRINTF("Error: invalid redirect type in lst_add_new_redirect\n");
        return (NULL);
    }
    if (*list_node == NULL)
        *list_node = new_node;
    else
    {
        while ((*list_node)->next)
            *list_node = (*list_node)->next;
        (*list_node)->next = new_node;
    }
    return (new_node);
} */

//creates a new t_arg node with ptr to arg str, and adds to back of args list
int add_arg_to_list(t_parser_lst *list_params, char *arg)
{
    t_arg    *node;

    node = malloc(sizeof(t_token));
    if (!node)
    {
        free(arg);
        error_free_and_exit(list_params, "malloc failed in add_arg_to_list");
    }
    node->arg = arg;
    node->next = NULL;
    if (!list_params->arg_head || !list_params->arg_tail)
        list_params->arg_head = node;
    else
        list_params->arg_tail->next = node;
    list_params->arg_tail = node;
    return (OK);
}