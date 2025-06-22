/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:34 by belinore          #+#    #+#             */
/*   Updated: 2024/11/20 21:09:00 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Parameters content:		The content to create the node with.
Return value:			The new node
External functs: 		malloc
Description:			Allocates (with malloc(3)) and returns a new node.
						The member variable ’content’ is initialized with
						the value of the parameter ’content’. The variable
						’next’ is initialized to NULL.
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*
int main (void)
{
	char *content = "Abc";
	t_list *first_element = ft_lstnew(content);
	if (!first_element)
		return (1);
	printf("First element content = %s\n", (char *)first_element->content);
	printf("First element next = %p\n", (void *)first_element->next);
}*/
