/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42Lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:34 by belinore          #+#    #+#             */
/*   Updated: 2024/11/19 14:10:53 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Parameters 		lst: The beginning of the list.
Return value 	The length of the list
Description		Counts the number of nodes in a list.
*/
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current_node;
	int		size;

	current_node = lst;
	size = 0;
	while (current_node != NULL)
	{
		size++;
		current_node = current_node->next;
	}
	return (size);
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
	ft_lstadd_front(first, new_element);
	printf("(*first)->content = %s\n", (char *)(*first)->content);
	printf("(*first)->next (ptr) = %p\n", (char *)(*first)->next);
	printf("(*first)->next->content = %s\n", (char *)(*first)->next->content);
	printf("(*first)->next->next = %p\n", (char *)(*first)->next->next);
	printf("\nft_lstsize:\n");
	printf("Size: %i", ft_lstsize(*first));
}*/
