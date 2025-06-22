/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42Lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:34 by belinore          #+#    #+#             */
/*   Updated: 2024/11/19 14:16:51 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Parameters 		lst: The beginning of the list.
Return value 	Last node of the list
Description		Returns the last node of the list.
*/
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current_node;

	if (lst == NULL)
		return (NULL);
	current_node = lst;
	while (current_node->next != NULL)
		current_node = current_node->next;
	return (current_node);
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
	ft_lstadd_front(first, new_element);
	new_element = ft_lstnew(content3);
	if (!new_element)
		return (1);
	ft_lstadd_front(first, new_element);
	printf("(*first)->content = %s\n", (char *)(*first)->content);
	printf("(*first)->next (node ptr) = %p\n", (char *)(*first)->next);
	printf("(*first)->next->content = %s\n", (char *)(*first)->next->content);
	printf("(*first)->next->next (node ptr)= %p\n",
		(char *)(*first)->next->next);
	printf("(*first)->next->next->content = %s\n",
		(char *)(*first)->next->next->content);
	printf("(*first)->next->next->next (node ptr)= %p\n",
		(char *)(*first)->next->next->next);
	printf("Last node content: %s", (char *)(ft_lstlast(*first))->content);
}*/
