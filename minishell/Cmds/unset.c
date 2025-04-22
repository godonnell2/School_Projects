#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
Deletes shell/environment variables so they no longer exist.
Affects Current Shell Only
Changes are not inherited by child processes (unlike export).
Works on Functions Too
Can also remove shell functions:
No Effect on Read-Only Variables
Fails silently (or with an error) if the variable is marked readonly.

Command	Description
unset VAR	Removes the variable VAR.

*/
typedef struct s_env_vars 
{
    char *key;
    char *value;
    struct s_env_vars *next;
} t_env_vars;


void ft_unset(t_env_vars **head, char *key)
{
    if(!head || !key)
        return;
    
    t_env_vars *curr = *head; 
    t_env_vars *prev = NULL; 

    while(curr)
    {
        if(ft_strcmp(curr->key, key) == 0)
        {
            if(prev)
            {
                prev->next = curr->next;
            }
            else
            {
                *head = curr->next;
            }
            free(curr->key);
            free(curr->value);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }

}