/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:50:59 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/10 21:01:54 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define EXIT_FAILURE 1

void	cleanup(t_stack *a, t_stack *b)
{
	free_stack(&a);
	free_stack(&b);
}

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**split_args;
	int		split_used;

	stack_a = NULL;
	stack_b = NULL;
	split_args = NULL;
	split_used = 0;
	if (ac < 2)
		return (0);
	if (ac == 2)
	{
		split_args = ft_split(av[1], ' ');
		if (!split_args || !is_valid_split(split_args))
		{
			free_arr(ac, split_args);
			err_case_nofree();
		}
		ac = count_split_args(split_args);
		av = split_args;
		split_used = 1;
	}
	check_args(ac, av);
	printf("ac:%d\n", ac);
	stack_a = add_args_to_stack(ac, av);
	if (!check_sorting(&stack_a))
	{
		if (split_used)
			free_arr(ac, av);
		free_stack(&stack_a);
		exit(1);
	}
	sorting(&stack_a, &stack_b);
	print_stack(stack_a, "sorted_stack");
	cleanup(stack_a, stack_b);
	if (split_used)
		free_arr(ac, av);
	return (0);
}
