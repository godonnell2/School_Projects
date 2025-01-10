/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 01:09:02 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/10 20:39:50 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_in_range(const char *str)
{
	long	num;

	num = ft_atol(str);
	if (num == LONG_MAX || num == LONG_MIN)
		return (0);
	if (num < INT_MIN || num > INT_MAX)
		return (0);
	return (1);
}

// Set the head pointer to NULL to indicate the stack is empty

void	free_stack(t_stack **head)
{
	t_stack	*curr;
	t_stack	*tmp;

	curr = *head;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	*head = NULL;
}
// indicate success return (0);
// Indicate an error return (-1);
// Avoid  producing empty strings due to extra spaces.

int	count_split_args(char **split_args)
{
	int	count;

	count = 0;
	while (split_args[count])
		count++;
	return (count);
}

int	is_valid_split(char **split_args)
{
	int	i;

	i = 1;
	while (split_args[i])
	{
		if (split_args[i][0] == '\0' || !is_numeric(split_args[i]))
			return (0);
		i++;
	}
	return (1);
}
