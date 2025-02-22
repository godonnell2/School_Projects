/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:14 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/10 21:01:26 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_top_two(t_stack **stack_head)
{
	int	temp_value;

	if (!(*stack_head) || !(*stack_head)->next)
		return ;
	temp_value = (*stack_head)->nbr;
	(*stack_head)->nbr = (*stack_head)->next->nbr;
	(*stack_head)->next->nbr = temp_value;
}

void	swap_stack_a(t_stack **stack_a)
{
	swap_top_two(stack_a);
	write(1, "sa\n", 3);
}

void	swap_stack_b(t_stack **stack_b)
{
	swap_top_two(stack_b);
	write(1, "sa\n", 3);
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