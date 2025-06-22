/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42Lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:34 by belinore          #+#    #+#             */
/*   Updated: 2024/11/19 15:26:46 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Parameters		lst: The node to free
			del: The address of the function used to delete the content.
External functs. 	free
Description		Takes as a parameter a node and frees the memory of
			the node’s content using the function ’del’ given
			as a parameter and free the node. The memory of
			’next’ must not be freed.		*/
#include "libft.h"

/*static void del(void *content_ptr)
{
	free(content_ptr);
}
*/
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
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
	printf("\nBefore ft_lstdelone:\n");
	printf("(*first)->content = %s\n", (char *)(*first)->content);
	printf("(*first)->next (node ptr) = %p\n", (char *)(*first)->next);
	printf("(*first)->next->content = %s\n", (char *)(*first)->next->content);
	printf("(*first)->next->next (node ptr)= %p\n", (*first)->next->next);
	printf("new_element->content (ptr) = %p\n", (char *)new_element->content);
	ft_lstdelone(first_element->next, del);
	printf("\nAfter ft_lstdelone:\n");
	printf("(*first)->content = %s\n", (char *)(*first)->content);
	printf("(*first)->next (node ptr) = %p\n", (char *)(*first)->next);
//	printf("(*first)->next->content = %s\n", (char *)(*first)->next->content);
	printf("new_element->content (ptr) = %p\n", (char *)new_element->content);

}*/
