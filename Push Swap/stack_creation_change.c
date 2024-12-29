/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_creation_change.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:19 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/29 10:54:45 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*add_args_to_stack(int ac, char **av)
{
	t_stack	*tmphead;
	int		i;

	tmphead = NULL;
	if (!av)
		return (NULL);
	if (ac == 2)
		i = 0;
	else
		i = 1;
	while (av[i])
	{
		insert_end(&tmphead, ft_atol(av[i]));
		i++;
	}
	return (tmphead);
}

int	struct_len(t_stack *stack)
{
	int	length;

	length = 0;
	while (stack)
	{
		length++;
		stack = stack->next;
	}
	return (length);
}

int	struct_sum(t_stack *stack)
{
	int	sum;

	sum = 0;
	while (stack)
	{
		sum += stack->nbr;
		stack = stack->next;
	}
	return (sum);
}

int	check_sorting(t_stack **a)
{
	t_stack	*curr;
	int		check;

	if (a == NULL || *a == NULL || (*a)->next == NULL)
		return (0);
	curr = *a;
	check = 0;
	while (curr->next)
	{
		if ((curr->nbr) > (curr->next->nbr))
			check++;
		curr = curr->next;
	}
	return (check);
}

void	insert_end(t_stack **head, int value)
{
	t_stack	*new_node;
	t_stack	*curr;

	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		exit(1);
	new_node->next = NULL;
	new_node->nbr = value;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
}
