/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:41 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/10 21:12:02 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#define MAX_ARGS 1000
#include <limits.h>

void	err_case_nofree(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

static void	err_case_free(int *nums)
{
	free(nums);
	err_case_nofree();
}

void	check_args(int ac, char **av)
{
	int			*nums;
	int			size;
	int			i;
	const char	*current_arg;

	size = ac - 1;
	nums = malloc(sizeof(int) * size);
	if (!nums)
		err_case_nofree();
	i = 0;
	while (i < size)
	{
		current_arg = av[i + 1];
		if (!is_numeric(current_arg) || !is_in_range(current_arg))
			err_case_free(nums);
		nums[i] = ft_atol(current_arg);
		i++;
	}
	if (has_duplicates(nums, size))
		err_case_free(nums);
	free(nums);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	has_duplicates(int *arr, int size)
{
	int	i;
	int	j;

	i = 1;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] == arr[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
