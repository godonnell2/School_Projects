/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:51 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/07 21:03:38 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_listhead;
	t_list	*tmp;

	new_listhead = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp == NULL)
		{
			ft_lstclear(&new_listhead, del);
			return (NULL);
		}
		if (new_listhead == NULL)
			new_listhead = tmp;
		else
			ft_lstadd_back(&new_listhead, tmp);
		lst = lst->next;
	}
	return (new_listhead);
}

/* 
check if lst or f or del is NULL 
loop over lst 
create a new element 
 if new elem is null,
 if a node creation fails you want to delete the whole list
  clear the new list 
 add the new element to the back of the list 
 finally, return the new list */