#include "libft.h"

void del(void *content);

void ft_lstdelone(t_list *lst, void (*del)(void *))
{
    if (lst == NULL)
        return;
    del(lst->content);
    free(lst);
}

/*
char g_deleted = 0;
void del(void *c)
{
    g_deleted = 1;
    free(c);
}

int main()
{
    t_list *node_first;
    node_first = ft_lstnew(ft_strdup("Grace"));

    ft_lstdelone(node_first, del);

    if (!g_deleted)
    {
        printf("FAILED: Delete function not called\n");
    }
    else
    {
        printf("Success, Grace is the best!\n");
    }

    return 0;
}
*/

/*
whenever im referencing the whole list its ** a ptr to a ptr
lst = NULL;  Set lst to NULL after deletion to avoid dangling pointer
CANT free a string literal. when assign content NEED to use malloc
therefore NEED strdup
https://almayor.github.io/libft/html/ft__lstdelone_8c.html
*/