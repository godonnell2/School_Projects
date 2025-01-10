/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:11 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/10 19:54:40 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rb(t_stack **b)
{
	rotate_stack(b);
	write(1, "rb\n", 3);
}

void	reverse_rotate_stack(t_stack **stack_head)
{
	t_stack	*current_lasttotop_node;
	t_stack	*second_last_node;

	if (!(*stack_head) || !(*stack_head)->next)
		return ;
	current_lasttotop_node = (*stack_head);
	while (current_lasttotop_node->next)
	{
		second_last_node = current_lasttotop_node;
		current_lasttotop_node = current_lasttotop_node->next;
	}
	second_last_node->next = NULL;
	current_lasttotop_node->next = *stack_head;
	*stack_head = current_lasttotop_node;
}

void	reverse_rotate_stack_a(t_stack **stack_a)
{
	reverse_rotate_stack(stack_a);
	write(1, "rra\n", 4);
}

void	reverse_rotate_stack_b(t_stack **stack_b)
{
	reverse_rotate_stack(stack_b);
	write(1, "rrb\n", 4);
}

#ifdef VERBOSE
void	print_stack(t_stack *s, char *comment)
{

	printf("stack:%s\n", comment);
	while (s)
	{
		printf("%d\n", s->nbr);
		s = s->next;
	}
	printf("----\n");
}
#else
void	print_stack(t_stack *s, char *comment)
{
	(void)s;
	(void)comment;
}
#endif

