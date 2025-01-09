/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:23 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/09 07:38:29 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	if (check_sorting(a) == 0)
	{
		return ;
	}  If already sorted, do nothing
*/
void	sorting(t_stack **a, t_stack **b)
{
	t_stack	*curr;
	int		len;

	if (a == NULL || *a == NULL)
		return ;
	curr = *a;
	len = 0;
	while (curr != NULL && ++len)
		curr = curr->next;
	if (check_sorting(a) == 0)
		return ;
	if (len == 1)
		return ;
	else if (len == 2)
		sort_2(a);
	else if (len == 3)
		sort_3(a);
	else if (len == 4)
		sort_4(a, b);
	else if (len == 5)
		sort_5(a, b);
	else if (len > 5)
		sort_greaterthanfive(a, b);
}

void	sort_2(t_stack **a)
{
	if ((*a)->nbr > (*a)->next->nbr)
		swap_stack_a(a);
}

/*
he function uses three conditional checks
 to determine the order of the three elements in the stack.
 The elements are accessed as follows:

(*a): The top element of the stack.
(*a)->next: The second element of the stack.
(*a)->next->next: The third element of the stack.
This condition checks if the second element is greater than the third element.
If true, it means the second element is the largest of the three after the
first condition has been checked.
If this condition is true, the function calls rra(a), which performs a
reverse rotation, moving the last element (which is now the largest)
to the top of the stack.
Let's consider the following initial state of Stack A:
Stack A: 2 -> 3 -> 1 for the second condition
*/

void	sort_3(t_stack **a)
{
	if ((*a)->nbr > (*a)->next->nbr && (*a)->nbr > (*a)->next->next->nbr)
		ra(a);
	if ((*a)->next->nbr > (*a)->next->next->nbr)
		reverse_rotate_stack_a(a);
	if ((*a)->next->nbr < (*a)->nbr)
		swap_stack_a(a);
}

void	sort_4(t_stack **a, t_stack **b)
{
	push_to_stack_b(a, b);
	sort_3(a);
	if (!((*b)->nbr > (*a)->next->nbr && (*b)->nbr < (*a)->next->next->nbr))
		push_to_stack_a(b, a);
	else
		pos_4(a, b);
	if ((*a)->nbr > (*a)->next->nbr && (*a)->nbr < (*a)->next->next->nbr)
		swap_stack_a(a);
	if ((*a)->nbr > (*a)->next->next->nbr)
		ra(a);
}

void	pos_4(t_stack **a, t_stack **b)
{
	reverse_rotate_stack_a(a);
	push_to_stack_a(b, a);
	ra(a);
	ra(a);
}
