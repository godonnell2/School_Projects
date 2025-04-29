#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
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
typedef struct s_env_vars 
{
    char *key;
    char *value;
    struct s_env_vars *next;
} t_env_vars;

t_env_vars *get_env_node(t_env_vars *head, const char *key) 
{
    while (head) 
    {
        if (ft_strcmp(head->key, key) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

char *ft_strdup(const char *s) 
{
    size_t len = 0;
    const char *p = s;
     if (!s)
      return NULL;

    while (*p++) 
    {
        len++;
    }
   
    char *dup = malloc(len + 1);
  if (!dup) 
  {
        perror("export: malloc in strdup");
        return NULL;
    }
    
   size_t i = 0;
   while(i < len) 
   {
        dup[i] = s[i]; 
        i++;
    }
    dup[i] = '\0';
    
    return dup;
}


void set_env_var(t_env_vars **head, const char *key, const char *value) 
{
      if (!key || !value) 
      {
        perror("export: not key or not value"); //error handle
        return;
    }
    t_env_vars *node = get_env_node(*head, key);

    if (node) 
    {
        char *new_value = ft_strdup(value);
        if(!new_value)
        {
            perror("export: fail strdup");
            return;
        }
        free(node->value);
        node->value = new_value;
    } 
    else 
    {
        node = malloc(sizeof(t_env_vars));
        if (!node)
        {
            perror( "export:malloc failed in set_env_var");
            return;
        }
        node->key = ft_strdup(key);
        node->value = ft_strdup(value);

         if (!node->key || !node->value) 
         {
            free(node->key);
            free(node->value);
            free(node);
            return;
         }
        node->next = *head;
        *head = node;
    }
}

void free_env_list(t_env_vars **head) {
    while (*head) 
    {
        t_env_vars *next = (*head)->next;
        free((*head)->key);
        free((*head)->value);
        free((*head));
        *head = next;
    }
}

/*


int main() {
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
    return 0;
}
*/