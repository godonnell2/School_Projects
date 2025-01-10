/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:08 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/10 20:29:15 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_top_element(t_stack **src_stack, t_stack **dst_stack)
{
	t_stack	*top_node;

	if (!(*src_stack))
	{
		return ;
	}
	top_node = *src_stack;
	*src_stack = (*src_stack)->next;
	top_node->next = *dst_stack;
	*dst_stack = top_node;
}

void	push_to_stack_b(t_stack **stack_a, t_stack **stack_b)
{
	move_top_element(stack_a, stack_b);
	write(1, "pb\n", 3);
}

void	push_to_stack_a(t_stack **stack_b, t_stack **stack_a)
{
	move_top_element(stack_b, stack_a);
	write(1, "pa\n", 3);
}

// or has only one element !(*stack_head)->next)
// Start from the new head  current_node = *stack_head;

void	rotate_stack(t_stack **stack_head)
{
	t_stack	*top_to_bottom_node;
	t_stack	*current_node;

	if (!(*stack_head) || !(*stack_head)->next)
		return ;
	top_to_bottom_node = *stack_head;
	*stack_head = top_to_bottom_node->next;
	current_node = *stack_head;
	while (current_node->next)
		current_node = current_node->next;
	current_node->next = top_to_bottom_node;
	top_to_bottom_node->next = NULL;
}

void	ra(t_stack **a)
{
	rotate_stack(a);
	write(1, "ra\n", 3);
}

#ifdef VERBOSE
void print_stack(t_stack *s, char * comment) 
{

	printf("stack:%s\n", comment);
	while (s) {
		printf("%d\n", s->nbr);
		s = s->next;
	}
	printf("----\n");
}
	#else
void print_stack(t_stack *s, char * comment)
{
	(void)s;
	(void)comment;
	
}
#endif