/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:19:00 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/06 13:19:01 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
} t_list
*/

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*ptr;

	count = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}
/*
int	main(void)
{
    t_list			*lst;
	t_list	*node_middle;
	t_list	*node_first;
	int		count;

    lst = NULL;
    t_list * node_final = ft_lstnew("best");
    ft_lstadd_front(&lst, node_final);
    node_middle = ft_lstnew("is the");
    ft_lstadd_front(&lst, node_middle);
    node_first = ft_lstnew("grace");
    ft_lstadd_front(&lst, node_first);
    count = ft_lstsize(node_first);
    printf("%d", count);
    return (0);
}
*/
/*
   ptr = ptr->next;
    need to put the ptr = ptr->next otherwise you werent doing anything!!
    while str!='\0' same as string you dont iterate in the while loop
    thats just teh condition so dont put equal to next there

HAVE TO PUT PTR EQUAL TO HEAD OF LIST OTHERWISE YOURE DOING NOTHING JUST AN 
EMPTY PTR
PTR HAS TO BE OF SAME TYPE

should do this in reality good practice
t_list				*current = lst;
    while (current != NULL) {
        t_list *next = current->next;
        free(current);
        current = next;

        NEED To PUT HEAD OF LIST LST = NULL or wont work!! undefined behaviour

        &lst is always the head. need to always add to the head
*/