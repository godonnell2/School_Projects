/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:17:05 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/08 09:34:42 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (lst == NULL || new == NULL)
		return ;
	ptr = *lst;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = new;
	}
}
/*
int	main(void)
{
	t_list	*lst;
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*current;

    lst = NULL;
    node1 = ft_lstnew("grace");
    node2 = ft_lstnew("is the ");
    node3 = ft_lstnew("best!");
 
    ft_lstadd_back(&lst, node1);
    ft_lstadd_back(&lst, node2);
    ft_lstadd_back(&lst, node3);
    current = lst;
    while (current != NULL) {
        printf("%s -> ", (char *)current->content);
        current = current->next;
    }
}
*/
/*

lst: The address of a pointer to the first link of
a list.
new: The address of a pointer to the node to be
added to the list.
  Now ptr points to the last node, set its next to new
   If the list is empty, set the new node as the head
   even when you add nodes to the back of the list you use 
   the address of the list because its like a string!!
    You should initialize ptr to point to the dereferenced list (*lst), 
    not to lst itself.
*/