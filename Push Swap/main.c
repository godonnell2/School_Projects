/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:50:59 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/26 00:51:00 by gro-donn         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_stack *stack_a = NULL;
	t_stack *stack_b = NULL;
	if (ac < 2)
	{
		err_case_nofree(); // Do not free argv
	}

	check_args(ac, av);

	stack_a = add_args_to_stack(ac, av);

	sorting(&stack_a, &stack_b);

	free_stack(&stack_a);
	free_stack(&stack_b);

	return (0);
}