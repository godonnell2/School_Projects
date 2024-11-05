#include "libft.h"

void ft_lstiter(t_list *lst, void (*f)(void *))
{
    t_list *ptr;
    ptr = lst;

    while(ptr !=NULL)
    {
        f(ptr->content);
        ptr = ptr->next;
    }
}
/*
void ft_print(void *content) {
    printf("%s\n", (char *)content);
}

int main()
{
      t_list *lst = ft_lstnew(ft_strdup("Grace"));
    lst->next = ft_lstnew(ft_strdup("is the "));
    lst->next->next = ft_lstnew(ft_strdup("best"));
    ft_lstiter(lst, ft_print);
    return 0;
}
*/