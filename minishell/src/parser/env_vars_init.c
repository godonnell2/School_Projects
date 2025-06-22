#include "minishell.h"

void free_env_vars(t_env_vars *env_vars)
{
    t_env_vars *next;

    while (env_vars)
    {
        next = env_vars->next;
        free(env_vars->key);
        free(env_vars->value);
        free(env_vars);
        env_vars = next;
    }
    DEBUG_LOG("freed env_vars list\n");
}

t_env_lst* env_var_new_tail_node(t_env_lst *list)
{
    list->current = malloc(sizeof(t_env_vars));
    if (list->current == NULL)
    {
        perror("malloc failed in env_var_new_tail_node");
        return (NULL);
    }
    list->current->next = NULL;
    if (list->head == NULL || list->tail == NULL)
        list->head = list->current;
    else
        list->tail->next = list->current;
    list->tail = list->current;
    return (list);
}

t_env_lst*  add_env_var(char *envp_str, t_env_lst *list)
{
    int        i;
    int        j;

    list = env_var_new_tail_node(list);
    if (list == NULL)
        return (NULL);
    i = 0;
    while (envp_str[i] && envp_str[i] != '=')
        i++;
    list->current->key = strdup_len(envp_str, i);
    if (envp_str[i] == '=')
        i++;
    j = 0;
    while (envp_str[i + j])
        j++;
    list->current->value = strdup_len(&envp_str[i], j);
    if (list->current->key == NULL || list->current->value == NULL)
    {
        free(list->current->key);
        free(list->current->value);
        perror("malloc failed in add_env_var");
        return (NULL);
    }
    return (list);
}

t_env_vars* get_env_vars(char **envp)
{
    t_env_lst      *list_setup;
    t_env_vars          *head;

    list_setup = malloc(sizeof(t_env_lst));
    if (list_setup == NULL)
    {
        perror("malloc failed in get_env_vars");
        return (NULL);
    }
    list_setup->head = NULL;
    list_setup->tail = NULL;
    while (*envp)
    {
        list_setup = add_env_var(*envp, list_setup);
        if (list_setup == NULL)
        {
            free_env_vars(list_setup->head);
            free(list_setup);
            return (NULL);
        }
        envp++;
    }
    head = list_setup->head;
    free(list_setup);
    return (head);
}