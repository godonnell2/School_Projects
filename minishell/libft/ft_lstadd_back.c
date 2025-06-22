/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42Lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:34 by belinore          #+#    #+#             */
/*   Updated: 2024/11/19 15:32:10 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Parameters	  lst: The address of a pointer to the first link of a list.
			  new: The address of a pointer to the node to be added to the list.
Description   Adds the node ’new’ at the end of the list.
*/
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current_node;

	current_node = ft_lstlast(*lst);
	if (current_node == NULL)
		*lst = new;
	else
		current_node->next = new;
}
/*
int main (void)
{
	char *content = "Abc";
	char *content2 = "Def";
	char *content3 = "Ghi";
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
	ft_lstadd_back(first, new_element);
	printf("\nAfter adding new element at the back:\n");
	printf("(*first)->content = %s\n", (char *)(*first)->content);
	printf("(*first)->next (ptr) = %p\n", (char *)(*first)->next);
	printf("(*first)->next->content = %s\n", (char *)(*first)->next->content);
	printf("(*first)->next->next = %p\n", (char *)(*first)->next->next);
	new_element = ft_lstnew(content3);
	if (!new_element)
		return (1);
	ft_lstadd_back(first, new_element);
	printf("\nAfter adding another new element at the back:\n");
	printf("(*first)->content = %s\n", (char *)(*first)->content);
	printf("(*first)->next (node ptr) = %p\n", (char *)(*first)->next);
	printf("(*first)->next->content = %s\n", (char *)(*first)->next->content);
	printf("(*first)->next->next (node ptr)= %p\n", (*first)->next->next);
	printf("(*f)->n->n->c = %s\n", (char *)(*first)->next->next->content);
	printf("(*f)->n->n->n (node ptr)= %p\n", (*first)->next->next->next);
	printf("Last node content: %s", (char *)(ft_lstlast(*first))->content);
}*/
