/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:02:07 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/08 09:35:33 by gro-donn         ###   ########.fr       */
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

n your ft_lstnew function, the content parameter is a pointer (void *content).
This means that when you create a new node, you are storing a pointer
			to some data in the content field of the node.
    When you assign new_node->content = content;, you are storing the 
	address of the data that content points to in the content field of the new 
	node.

Using &test:

    If test is a variable (e.g., an integer, a struct, etc.), using &test 
	gives you the address of that variable. This is important because the 
	linked list is designed to store pointers to data, not the data itself.
	Passing &one (a pointer to one) allows ft_lstnew to store a reference
	 to the int value in one without directly copying or modifying it. 
	 If you passed one directly (just the integer 1), you would need to cast
	  it to (void *)1 to store it in a void * pointer, which isn't safe or 
	  reliable. Using a pointer to the actual value is much more reliable.
*/