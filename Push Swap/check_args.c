/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:41 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/29 11:03:41 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#define MAX_ARGS 1000
#include <limits.h>

void	err_case(int ac, char **av)
{
	write(2, "Error\n", 6);
	free_arr(ac, av);
	exit(1);
}

void	err_case_nofree(void)
{
	write(2, "Error\n", 6);
	exit(1);
}
/*
The err_case function is well-structured, but:

It assumes free_arr will properly handle av even though av
 may not always be dynamically allocated (e.g., in a typical main program,
 argv from int main(int argc, char **argv) isn't dynamically allocated).
 This can cause a double-free or invalid free error.
 free_arr tries to free av as though it were dynamically allocated.
 If av points to argv from main, this will result in undefined behavior.
 Only dynamically allocated memory should be freed.

Fix: Pass a flag indicating whether av is dynamically allocated or ensure
 it’s dynamically allocated before calling free_arr.
 */

void	check_args(int ac, char **av)
{
	check_ints(ac, av);
	init_checkdup(ac, av);
	check_fitint(ac, av);
}

void	check_ints(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	(void)ac;
	while (av[i])
	{
		j = 0;
		if ((av[i][j] == '-' || av[i][j] == '+') && av[i][j + 1] != '\0')
			j++;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				err_case_nofree();
			j++;
		}
		i++;
	}
}

void	check_duplicates(int ac, char **av, char **seen, int i)
{
	int			j;
	static int	count = 0;

	if (i >= ac)
	{
		return ;
	}
	j = 0;
	while (j < count)
	{
		if (ft_strcmp(av[i], seen[j]) == 0)
		{
			err_case_nofree(); // NEED CHECK VALGRIND
		}
		j++;
	}
	if (count < MAX_ARGS)
	{
		seen[count] = av[i];
		count++;
	}
	check_duplicates(ac, av, seen, i + 1);
}
