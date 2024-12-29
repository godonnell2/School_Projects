/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:39 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/26 00:51:40 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotation_b(t_stack **b, int index)
{
	int	rotation;
	int	rrotation;
	int	len;

	len = struct_len(*b) + 1;
	rotation = index - 1;
	rrotation = len - index;
	if (rotation < rrotation)
	{
		while (rotation)
		{
			rb(b);
			rotation--;
		}
	}
	else
	{
		while (rrotation)
		{
			reverse_rotate_stack_b(b);
			rrotation--;
		}
	}
}

void	sort_greaterthanfive(t_stack **a, t_stack **b)
{
	int	s_len;
	int	s_sum;
	int	mean;

	s_len = struct_len(*a);
	while (s_len > 5)
	{
		s_sum = struct_sum(*a);
		mean = s_sum / s_len;
		if ((*a)->nbr < mean)
			push_to_stack_b(a, b);
		else
			ra(a);
		s_len = struct_len(*a);
	}
	call_functions(a, b);
}

/*
Sort the first five elements in stack A
While there are elements in stack B
Assign indices to elements in stack A
Assign indices to elements in stack B
Find the best friend index for each node in stack B
// Calculate the cost for each node in stack B
 // Move the node with the minimum cost to the top of stack A
 / Perform any final rotations to ensure stack A is sorted
*/
void	call_functions(t_stack **a, t_stack **b)
{
	sort_5(a, b);
	while ((*b))
	{
		add_index(a);
		add_index(b);
		add_best_friend(*a, b);
		add_cost(a, b);
		moves_top(a, b);
	}
	last_rotates(a);
}

/*After processing all elements in stack B, last_rotates(a) is called.*/
void	last_rotates(t_stack **a)
{
	while (check_sorting(a))
		ra(a);
}