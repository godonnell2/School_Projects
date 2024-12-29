/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:35 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/26 00:51:36 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_moves_to_top(t_stack *node, int index)
{
	int	ra;
	int	rra;
	int	len;

	len = struct_len(node) + 1;
	ra = index - 1;
	rra = len - index;
	if (ra < rra)
		return (ra);
	else
		return (rra);
}
/*
get_moves(*a, curr->best): This call calculates the number of moves required to
 bring the node in stack A (identified by curr->best) to the top of stack A.
get_moves(*b, curr->index): This call calculates the number of moves required
to bring the current node in stack B (identified by curr->index) to the top
of stack B.
The total cost is the sum of these two values, which is then assigned to the
 cost member of the current node.
 Let’s illustrate how add_cost works with an example.

Initial State
Assume we have the following stacks:

Stack A:

Node 1: nbr = 5, index = 0, best = 2 (the index of the closest greater element)
Node 2: nbr = 10, index = 1, best = 3
Node 3: nbr = 15, index = 2, best = 4
Stack B:

Node 1: nbr = 8, index = 0, cost = -1 (uninitialized)
Node 2: nbr = 12, index = 1, cost = -1
Node 3: nbr = 18, index = 2, cost = -1
Execution of add_cost
For Node 1 in Stack B (nbr = 8, index = 0, best = 2):
Call	get_moves(*a, 2) to calculate the moves needed to bring the node with

index = 2 in stack A to the top.
Assume get_moves returns 1 (it takes 1 move).
Call	get_moves(*b, 0) to calculate the moves needed to bring the current
node in stack B
*/
void	add_cost(t_stack **a, t_stack **b)
{
	t_stack	*curr;

	curr = *b;
	while (curr)
	{
		curr->cost = get_moves_to_top(*a, curr->best) + get_moves_to_top(*b,
				curr->index);
		curr = curr->next;
	}
}
/*
Purpose: This function moves the node from stack B with the
minimum cost to the top of stack A.
*/
void	moves_top(t_stack **a, t_stack **b)
{
	t_stack	*curr;

	curr = *b;
	while (curr)
	{
		if (curr->cost == cost_win(*b))
		{
			rotation_a(a, curr->best);
			rotation_b(b, curr->index);
			push_to_stack_a(b, a);
			break ;
		}
		curr = curr->next;
	}
}

/*
Purpose: This function finds the minimum cost among all nodes in stack B.

It initializes cost to INT_MAX and iterates through each node in stack B.
If a node's cost is less than the current minimum cost, it updates cost.
*/

int	cost_win(t_stack *b)
{
	int		cost;
	t_stack	*curr;

	cost = INT_MAX;
	curr = b;
	while (curr)
	{
		if (curr->cost < cost)
			cost = curr->cost;
		curr = curr->next;
	}
	return (cost);
}

/*
Purpose: This function rotates stack A to bring the node at the specified index
 to the top.


*/
void	rotation_a(t_stack **a, int index)
{
	int rotation;
	int rrotation;
	int len;

	len = struct_len(*a) + 1;
	rotation = index - 1;
	rrotation = len - index;
	if (rotation < rrotation)
	{
		while (rotation)
		{
			ra(a);
			rotation--;
		}
	}
	else
	{
		while (rrotation)
		{
			reverse_rotate_stack_a(a);
			rrotation--;
		}
	}
}