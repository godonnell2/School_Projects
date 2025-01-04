/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:50:59 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/04 14:31:35 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define EXIT_FAILURE 1

void	cleanup_and_exit(int ac, char **av, t_stack *a, t_stack *b)
{
	free_arr(ac, av);
	free_stack(&a);
	free_stack(&b);
	exit(EXIT_FAILURE);
}

void	cleanup(int ac, char **av, t_stack *a, t_stack *b)
{
	free_arr(ac, av);
	free_stack(&a);
	free_stack(&b);
}

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_b = NULL;
	if (ac < 2)
		err_case_nofree();
	validate_args(av);
	if (ac == 2)
		av = ft_split(av[1]);
	check_args(ac, av);
	stack_a = add_args_to_stack(ac, av);
	if (!check_sorting(&stack_a))
	{
		free_arr(ac, av);
		free_stack(&stack_a);
		exit(1);
	}
	sorting(&stack_a, &stack_b);
	cleanup(ac, av, stack_a, stack_b);
	return (0);
}
