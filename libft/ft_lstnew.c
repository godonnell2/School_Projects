/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:02:07 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/04 16:11:48 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/*
int	main(void)
{
	int		test;
	t_list	*node;

	test = 42;
	node = ft_lstnew(&test);
	if(node == NULL)
	{
		printf("failed to create node");
		return (1);
	}
	if (node -> content == &test)
	printf("correctly assigned value, YAY\n");
	else
		printf("did not assign value, FAIL \n");
	if(node-> next == NULL)
	{
		printf("next node is null, YAY\n");
	}
	else
	printf("node is not null,,FAIL\n");
	free(node);
	return (0);
}
*/

/*
a node is another point of the tlist struct ie BOTH a piece of content
and a ptr to the next linked data point
You want to store the variable's value in the linked list node: The
 linked list node needs to point to the actual data,
not just a copy of it. By passing the address, the node can access the
original variable's value.
	if(*(int *)node -> content == 42) ||
	if (node -> content == &test)
*/