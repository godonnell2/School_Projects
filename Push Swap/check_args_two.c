/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 01:09:02 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/29 11:00:00 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_checkdup(int ac, char **av)
{
	char	*seen[MAX_ARGS];

	ft_memset(seen, 0, sizeof(seen));
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

int	ft_split_and_update(int *argc, char ***argv)
{
	char	**split_args;

	split_args = ft_split((*argv)[1]);
	if (!split_args)
	{
		return (-1);
	}
	*argc = 0;
	while (split_args[*argc])
		(*argc)++;
	*argv = split_args;
	return (0);
}
