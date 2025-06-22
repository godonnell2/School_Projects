/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42Lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:34 by belinore          #+#    #+#             */
/*   Updated: 2024/11/19 16:33:06 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Parameters		lst: The address of a pointer to a node.
			del: The address of the function used to iteratr on
					the list.
Description		Iterates the list ’lst’ and applies the function
			’f’ on the content of each node.*/

#include "libft.h"

/*
static void	overwrite(void *content_ptr)
{
	int				i;
	unsigned char	*content;

	i = 0;
	content = (unsigned char *)content_ptr;
	while (content[i])
	{
		content[i] = 'X';
		i++;
	}
}*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list			*current_node;

	current_node = lst;
	while (current_node)
	{
		f(current_node->content);
		current_node = current_node->next;
	}
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
	ft_lstadd_back(first, new_element);
	new_element = ft_lstnew(content3);
	if (!new_element)
		return (1);
	ft_lstadd_back(first, new_element);
	printf("\nBefore ft_lstiter:\n");
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
	ft_lstiter(first_element, overwrite);
	printf("\nAfter ft_lstiter:\n");
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
}*/
