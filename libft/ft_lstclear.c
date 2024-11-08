/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:17:59 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/08 18:15:47 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;

	if (*lst == NULL)
		return ;
	while (*lst != NULL)
	{
		ptr = *lst;
		del(ptr->content);
		*lst = (*lst)->next;
		free(ptr);
	}
}

/*char	g_deleted = 0;

void	del(void *c)
{
	g_deleted = 1;
	free(c);
}
*/
/*
int	main(void)
{
      t_list *node_first;

    node_first = ft_lstnew(ft_strdup("Grace"));
    ft_lstclear(&node_first, del);
      if (!g_deleted)
    {
        printf("FAILED: Delete function not called\n");
    }
    else
    {
        printf("Success, Grace is the best!\n");
    }
    return (0);
}
*/
/*
Why Parentheses Are Needed
Without parentheses, the expression *lst->next would be interpreted differently
 due to operator precedence:

In C, the -> operator has higher precedence than the * operator. This
 means that *lst->next would first evaluate lst->next as if lst were a pointer
  to a t_list (which it is not; lst is a pointer to a pointer).

This would lead to an incorrect dereference attempt, which can cause undefined 
behavior or a segmentation fault because lst is a pointer to a pointer, not a 
direct pointer to a t_list.
*/