/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:34 by belinore          #+#    #+#             */
/*   Updated: 2024/11/20 21:06:56 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Parameters 	lst: The address of a pointer to the first link of a list.
			new: The address of a pointer to the node to be added to the list.
Description Adds the node ’new’ at the beginning of the list.
*/
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
int main (void)
{
	char *content = "Abc";
	char *content2 = "Def";
	t_list *first_element;
	t_list *new_element;
	t_list **first;

	first_element = ft_lstnew(content);
	if (!first_element)
		return (1);
	first = &first_element;
	new_element = ft_lstnew(content2);
	if (!new_element)
		return (1);
	printf("Before adding new element:\n");
	printf("(*first)->content = %s\n", (char *)(*first)->content);
	printf("(*first)->next = %p\n", (char *)(*first)->next);
	ft_lstadd_front(first, new_element);
	printf("\nAfter adding new element at the front:\n");
	printf("(*first)->content = %s\n", (char *)(*first)->content);
	printf("(*first)->next (ptr) = %p\n", (char *)(*first)->next);
	printf("(*first)->next->content = %s\n", (char *)(*first)->next->content);
	printf("(*first)->next->next = %p\n", (char *)(*first)->next->next);
}*/
