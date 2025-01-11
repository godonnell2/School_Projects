/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:32 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/11 09:27:30 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void sort_5(t_stack **a, t_stack **b)
{
	push_to_stack_b(a, b);
	sort_4(a, b);
	if ((*b)->nbr > (*a)->next->nbr && (*b)->nbr < (*a)->next->next->nbr)
		pos_3(a, b);
	else if ((*b)->nbr > (*a)->next->next->nbr && (*b)->nbr < (*a)->next->next->next->nbr)
		pos_4(a, b);
	else if ((*b)->nbr < (*a)->nbr)
		push_to_stack_a(b, a);
	else if ((*b)->nbr > (*a)->nbr && (*b)->nbr < (*a)->next->nbr)
	{
		push_to_stack_a(b, a);
		swap_stack_a(a);
	}
	else if ((*b)->nbr > (*a)->next->next->nbr)
	{
		push_to_stack_a(b, a);
		ra(a);
	}
}

void pos_3(t_stack **a, t_stack **b)
{
	reverse_rotate_stack_a(a);
	reverse_rotate_stack_a(a);
	push_to_stack_a(b, a);
	ra(a);
	ra(a);
	ra(a);
}

int find_best_friend(t_stack *a, int nbr_b)
{
	int friend;
	int best;
	int temp;

	friend = INT_MAX;
	best = INT_MAX;
	while (a)
	{
		temp = a->nbr - nbr_b;
		if (temp < friend && a->nbr > nbr_b)
		{
			friend = temp;
			best = a->index;
		}
		a = a->next;
	}
	if (best == INT_MAX)
		return (-1);
	return (best);
}

void set_best_friend(t_stack *a, t_stack **b)
{
	t_stack *curr_b;

	curr_b = *b;
	while (curr_b)
	{
		curr_b->best = find_best_friend(a, curr_b->nbr);
		curr_b = curr_b->next;
	}
}

void set_index(t_stack **node)
{
	t_stack *curr;
	int i;

	curr = *node;
	i = 1;
	while (curr)
	{
		curr->index = i++;
		curr = curr->next;
	}
}

/*
nbr_b is the value from a node in stack B for which
you want to find the closest greater value in stack A
This function finds the "best friend" for a given number (nbr_b) from stack A.
It looks for the closest value in stack A that is greater than nbr_b
and returns the index of that value.

The set_best_friend function assigns a "best friend" index to each node in
 stack B based on the values in stack A. The "best friend" is the index
 of the closest element in stack A that is greater than
   the value of the current node in stack B.

   This function set_best_friend assigns a "best friend" index to each node
	in stack B based on the values in stack A.
It iterates through each node in stack B and calls the find_best_friend fn to find
 the closest value in stack A that is greater than the current node's value.

 This function assigns an index to each node in the stack.
It starts from the head of the stack and assigns an increasing
index (starting from 1) to each node as it traverses the stack.
*/