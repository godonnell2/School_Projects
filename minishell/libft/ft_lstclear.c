/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42Lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:34 by belinore          #+#    #+#             */
/*   Updated: 2024/11/19 16:47:04 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Parameters		lst: The address of a pointer to a node.
			del: The address of the function used to delete
					the content of the node.
External functs. 	free
Description		Deletes and frees the given node and every
			successor of that node, using the function ’del’
			and free(3).
			Finally, the pointer to the list must be set to NULL.*/
#include "libft.h"
/*
static void	del(void *content_ptr)
{

	free(content_ptr);
}*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_node;
	t_list	*next_node;

	current_node = *lst;
	while (current_node)
	{
		next_node = current_node->next;
		ft_lstdelone(current_node, del);
		current_node = next_node;
	}
	*lst = NULL;
}
/*
int main (void)
{
	char *content = ft_strdup("Abc");
	char *content2 = ft_strdup("Def");
	char *content3 = ft_strdup("Ghi");
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
	printf("(*first)->next->next (node ptr)= %p\n",
		(char *)(*first)->next->next);
	printf("(*first)->next->next->content = %s\n",
		(char *)(*first)->next->next->content);
	printf("(*first)->next->next->next (node ptr)= %p\n",
		(char *)(*first)->next->next->next);
	printf("new_element = %s\n", (char *)new_element->content);
	printf("new_element = %p\n", (char *)new_element->content);
	printf("Last node content: %s\n", (char *)(ft_lstlast(*first))->content);
	ft_lstclear(&first_element->next, ft_lstdelone);
	first_element->next->next = NULL;
	printf("new_element = %p\n", (char *)new_element->content);
	printf("Last node content: %s\n", (char *)(ft_lstlast(*first))->content);
}*/
