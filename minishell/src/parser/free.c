#include "minishell.h"

void    free_args_list(t_parser_lst *list)
{
    t_arg   *current_arg;
    t_arg   *next_arg;

    current_arg = list->arg_head;
    while (current_arg)
    {
        next_arg = current_arg->next;
        free(current_arg);
        current_arg = next_arg;
    }
    list->arg_head = NULL;
    list->arg_tail = NULL;
    DEBUG_LOG("freed args list\n");
}

void    free_tokens_list(t_parser_lst *list)
{
    t_token   *current_node;
    t_token   *next_node;

    current_node = list->token_head;
    while (current_node)
    {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    list->token_head = NULL;
    list->token_tail = NULL;
    DEBUG_LOG("freed tokens list\n");
}

void    free_redirect_list(t_redirect **head)
{
    t_redirect *next_node;
    t_redirect *node;

    node = *head;
    while (node)
    {
        next_node = node->next;
        free(node->target);
        close_if_not_std(node->heredoc_fd);
        free(node);
        node = next_node;
    }
    *head = NULL;
    DEBUG_LOG("freed redirects list\n");
}

void    free_str_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
    DEBUG_LOG("freed str_array\n");
}

void    free_command(t_command *command)
{
    if (command->redirs)
        free_redirect_list(&command->redirs);
    if (command->args)
    {
        free_str_array(command->args);
        command->args = NULL;
    }
    if (command->full_path)
    {
        free(command->full_path);
        command->full_path = NULL;
    }
    free(command);
}

void    free_commands_list(t_command *head)
{
    t_command *next_node;

    while (head)
    {
        next_node = head->next;
        free_command(head);
        head = next_node;
    }
    DEBUG_LOG("freed commands list\n");
}


