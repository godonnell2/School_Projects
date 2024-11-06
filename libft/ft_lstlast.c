/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:46 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/06 13:18:47 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	if (lst == NULL)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}
/*
int	main(void)
{
	t_list	*lst;
	t_list	*final;
	t_list	*middle_node;
	t_list	*first_node;
	t_list	*result;

    lst = NULL;
    final = ft_lstnew("the best");
    middle_node = ft_lstnew("is");
    first_node = ft_lstnew("Grace");
    ft_lstadd_front(&lst, final);
     ft_lstadd_front(&lst, middle_node);
     ft_lstadd_front(&lst, first_node);
    result = ft_lstlast(lst);
    printf("%p\n", result);
      printf("Last node content: %s\n", (char *)result->content);
    return(0);
}
*/
/*
0x0%   THIS MEANS YOURE RETURNING NULL BY ACCIDENT!!

ALWAYS NEED TO CHECK IF LST WAS NULL liek its a string
lst: The beginning of the list.
Return value: Last node of the list
Description Returns the last node of the list.
void	ft_lstadd_front(t_list **lst, t_list *new)
{
    if(new == NULL)
        return ;
  new -> next = *lst;
  *lst = new;  
}

For example, consider a linked list with three nodes: A -> B -> C -> NULL.

In ft_lstsize, the loop will iterate through A, B, and C, resulting in a 
count of 3.
In ft_lstlast, the loop will iterate through A and B, and when it 
reaches C, ptr->next will be NULL, causing the loop to exit and returning C.

*/