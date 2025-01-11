/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:39 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/11 09:56:04 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void rotate_to_top_b(t_stack **b, int index)
{
	int rotation;
	int rrotation;
	int len;

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

void findmean_below_pushb(t_stack **a, t_stack **b)
{
	int s_len;
	int s_sum;
	int mean;

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
	sort_greater_than_five(a, b);
}

void sort_greater_than_five(t_stack **a, t_stack **b)
{
	sort_5(a, b);
	while ((*b))
	{
		set_index(a);
		set_index(b);
		set_best_friend(*a, b);
		set_cost(a, b);
		moves_top(a, b);
	}
	rotate_to_finalpos(a);
}

void rotate_to_finalpos(t_stack **a)
{
	while (check_sorting(a))
		ra(a);
}

/*After processing all elements in stack B, rotate_to_finalpos(a) is called.
 It calculates the length of stack A and continues processing until
 there are five or fewer elements left.
It calculates the sum and mean of the elements in stack A.
If the top element of stack A is less than the mean, it pushes that element
to stack B. Otherwise, it rotates stack A.
After reducing the size of stack A to five or fewer, it calls
sort_greater_than_five(a, b) to handle the remaining elements.
*/