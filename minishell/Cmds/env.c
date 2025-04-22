#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void env(t_env_vars *head)
{
    while (head)
    {
        if (head->key && head->value)
            printf("%s=%s\n", head->key, head->value);
        head = head->next;
    }
}