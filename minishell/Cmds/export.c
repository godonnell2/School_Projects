#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
The export command in Unix/Linux shells is used to set environment variables,
making them available to child processes of the current shell session.

Key Points:
Environment Variables: These are key-value pairs that affect how running
processes behave.

Current Shell Only: By default, variables are local to the current shell.
export makes them available to subprocesses (like scripts or commands you run).

Syntax:
export VARIABLE=value
*/
/*
handle case sensitivity this is correct right as bash treats them separately
do i need to check validity of export key words??
plus need to handle malloc fail in strdup right now im just losing the var!!!!
*/

void	print_export(t_env_vars *env)
{
	while (env)
	{
		if (env->key)
		{
			printf("declare -x %s", env->key);
			if (env->value)
				printf("=\"%s\"", env->value);
			printf("\n");
		}
		env = env->next;
	}
	
}

char	*ft_strdup(const char *s)
{
	size_t		len;
	const char	*p = s;
	char		*dup;
	size_t		i;

	len = 0;
	if (!s)
		return (NULL);
	while (*p++)
		len++;
	dup = malloc(len + 1);
	if (!dup)
	{
		perror("export: malloc in strdup");
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	set_env_var(t_env_vars **head, const char *key, const char *value)
{
	t_env_vars	*node;
	char		*new_value;
	int exit_code; 
	if (!key || !value)
	{
		perror("export: invalid key or value");
		return exit_code = 1;
	}
	node = get_env_node(*head, key);
	if (node)
	{
		new_value = ft_strdup(value);
		free(node->value);
		node->value = new_value;
		return 0;
	}
	else
	{
		node = create_endnode(key, value);
		if (!node)
			return 1;
		node->next = *head;
		*head = node;
		return 0;
	}
}

t_env_vars	*create_endnode(const char *key, const char *value)
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
}

void	free_env_list(t_env_vars **head)
{
	t_env_vars	*next;

	while (*head)
	{
		next = (*head)->next;
		free((*head)->key);
		free((*head)->value);
		free((*head));
		*head = next;
	}
}

/*

int	main(void) {
	t_env_vars *env_list = NULL;

	// Set some variables
	set_env_var(&env_list, "USER", "alice");
	set_env_var(&env_list, "PATH", "/usr/bin");
	set_env_var(&env_list, "SHELL", "/bin/bash");

	// Update an existing variable
	set_env_var(&env_list, "PATH", "/usr/local/bin");

	// Print all environment variables
	printf("Environment variables:\n");
	t_env_vars *current = env_list;
	while (current) {
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}

	// Test getting a specific variable
	const char *query = "SHELL";
	t_env_vars *result = get_env_node(env_list, query);
	if (result) {
		printf("\nFound %s: %s\n", query, result->value);
	} else {
		printf("\n%s not found\n", query);
	}

	// Free memory
	free_env_list(&env_list);
	return (0);
}
*/