/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42Lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:34 by belinore          #+#    #+#             */
/*   Updated: 2024/11/20 20:40:26 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Parameters		lst: The address of a pointer to a node.
			f: The address of the function used to iterate on
					the list.
			del: The address of the function used to delete
				the content of a node if needed.
Return value		The new list.
			NULL if the allocation fails.
External functs.	malloc, free
Description		Iterates the list ’lst’ and applies the function
			’f’ on the content of each node. Creates a new
			list resulting of the successive applications of
			the function ’f’. The ’del’ function is used to
			delete the content of a node if needed.*/

#include "libft.h"

/*
static void	del(void *content_ptr)
{
	free(content_ptr);
}*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current_node;
	t_list	*content;
	t_list	*new_list_node;
	t_list	*new_list_head;

	current_node = lst;
	new_list_head = NULL;
	while (current_node)
	{
		content = f(current_node->content);
		new_list_node = ft_lstnew(content);
		if (new_list_node == NULL)
		{
			del(content);
			ft_lstclear(&new_list_head, del);
			return (NULL);
		}
		if (new_list_head == NULL)
			new_list_head = new_list_node;
		else
			ft_lstadd_back(&new_list_head, new_list_node);
		current_node = current_node->next;
	}
	return (new_list_head);
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
	t_list *new_list_head;

	first_element = ft_lstnew(content);
	if (!first_element)
		return (1);
	first = &first_element;
	new_element = ft_lstnew(content2);
	if (!new_element)
		return (1);
	ft_lstadd_back(first, new_element);
	new_element = ft_lstnew(content3);
	if (!new_element)
		return (1);
	ft_lstadd_back(first, new_element);
	printf("\nBefore ft_lstmap:\n");
	printf("(*first)->content = %s (%p)\n", (char *)(*first)->content,
		(*first)->content);
	printf("(*first)->next (node ptr) = %p\n", (char *)(*first)->next);
	printf("(*first)->next->content = %s\n", (char *)(*first)->next->content);
	printf("(*first)->next->next (node ptr)= %p\n",
		(char *)(*first)->next->next);
	printf("(*first)->next->next->content = %s\n",
		(char *)(*first)->next->next->content);
	printf("(*first)->next->next->next (node ptr)= %p\n",
		(char *)(*first)->next->next->next);

	new_list_head = ft_lstmap(first_element, (void *)ft_strdup, del);

	printf("\nAfter ft_lstmap:\n");
	printf("1) Original list (no change):\n");
	printf("(*first)->content = %s (%p)\n", (char *)(*first)->content,
		(*first)->content);
	printf("(*first)->next (node ptr) = %p\n", (char *)(*first)->next);
	printf("(*first)->next->content = %s\n", (char *)(*first)->next->content);
	printf("(*first)->next->next (node ptr)= %p\n",
		(char *)(*first)->next->next);
	printf("(*first)->next->next->content = %s\n",
		(char *)(*first)->next->next->content);
	printf("(*first)->next->next->next (node ptr)= %p\n",
		(char *)(*first)->next->next->next);
	printf("\n2) New list using ft_strdup as f:\n");
	printf("new_list_head->content = %s (%p)\n", (char *)new_list_head->content,
		new_list_head->content);
	printf("new_list_head->next (node ptr) = %p\n",
		(char *)new_list_head->next);
	printf("new_list_head->next->content = %s\n",
		(char *)new_list_head->next->content);
	printf("new_list_head->next->next (node ptr)= %p\n",
		(char *)new_list_head->next->next);
	printf("new_list_head->next->next->content = %s\n",
		(char *)new_list_head->next->next->content);
	printf("new_list_head->next->next->next (node ptr)= %p\n",
		(char *)new_list_head->next->next->next);
}*/
