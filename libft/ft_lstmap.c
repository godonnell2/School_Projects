/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:51 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/06 13:18:52 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    if(!lst )
        return  NULL;

    t_list *ptr = lst;
    while(ptr !=NULL)
    {
        if(ptr -> content != NULL)
        {
            ft_lstdelone(ptr, del);
        }
        ptr->next;
        f(ptr -> content);
  
    }
    return ptr;
}

void ft_print(void *content)
{
    printf("%s", (char *)content);
}

int main()
{
    t_list *lst = ft_lstnew(ft_strdup("Grace"));
    t_list *second_node = ft_lstnew(ft_strdup("is the"));
    t_list *final_node = ft_lstnew(ft_strdup("best"));

   ft_lstadd_back( &lst, second_node);
   ft_lstadd_back(&lst, final_node);

    ft_lstmap(lst, ft_print, ft_lstdelone);
    return(0);
}
*/