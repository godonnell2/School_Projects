/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 01:09:02 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/26 01:09:18 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_checkdup(int ac, char **av)
{
	char	*seen[MAX_ARGS] = {0};

	check_duplicates(ac, av, seen, 1);
}

void	check_fitint(int ac, char **av)
{
	int		i;
	long	num;

	i = 1;
	while (i < ac)
	{
		num = ft_atol(av[i]);
		if (num > INT_MAX || num < INT_MIN)
			err_case_nofree(); // NEED CHECK VALGRIND
		i++;
	}
}

void	free_stack(t_stack **head)
{
	t_stack	*curr;
	t_stack	*tmp;

	curr = *head; // Start with the head of the stack
	while (curr)  // Loop until there are no more nodes
	{
		tmp = curr;        // Store the current node in tmp
		curr = curr->next; // Move to the next node
		free(tmp);         // Free the memory of the current node
	}
	*head = NULL; // Set the head pointer to NULL to indicate the stack is empty
}

int	ft_split_and_update(int *argc, char ***argv)
{
	char	**split_args;

	split_args = ft_split((*argv)[1]);
	if (!split_args)
	{
		return (-1); // Indicate an error
	}
	*argc = 0;
	while (split_args[*argc])
		(*argc)++;
	*argv = split_args;
	return (0); // Success
}
