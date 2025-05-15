#include "minishell.h"

//cc -Wall -Wextra lst_env_vars.c

//note: cant use grace function as I need to use strdup_len for key and value

/* t_env_vars	*create_endnode(const char *key, const char *value)
{
	t_env_vars	*node;

	node = malloc(sizeof(t_env_vars));
	if (!node)
	{
		perror("export:malloc failed in set_env_var");
		return (NULL);
	}
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	if (!node->key || !node->value)
	{
		if (node->key)
			free(node->key);
		if (node->value)
			free(node->value);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
} */
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
    if (list->tail == NULL)
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


t_env_vars *get_env_node(t_env_vars *env_vars, const char *key) 
{

    while (env_vars) {
       
        if (ft_strcmp(env_vars->key, key) == 0) {
           
            return env_vars;
        }
        env_vars = env_vars->next;
    }
    printf("Variable %s not found\n", key);
    return NULL;
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
            free(list_setup);
            return (NULL);
        }
        envp++;
    }
    head = list_setup->head;
    free(list_setup);
    return (head);
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

