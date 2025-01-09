/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:50:59 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/09 07:46:18 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// 0 is used as `ac` here because it's no longer relevant
void	cleanup_resources(t_stack *stack_a, t_stack *stack_b, char **split_args,
		int split_used)
{
	free_stack(&stack_a);
	free_stack(&stack_b);
	if (split_used)
		free_arr(0, split_args);
}

void	validate_and_initialize(int ac, char **av, t_stack **stack_a)
{
	check_args(ac, av);
	*stack_a = add_args_to_stack(ac, av);
	if (!*stack_a)
	{
		err_case_nofree();
	}
	if (!check_sorting(stack_a))
	{
		free_stack(stack_a);
		exit(EXIT_FAILURE);
	}
}

void	handle_single_argument(int *ac, char ***av, char ***split_args,
		int *split_used)
{
	*split_args = ft_split((*av)[1], ' ');
	if (!(*split_args) || !is_valid_split(*split_args))
	{
		free_arr(*ac, *split_args);
		err_case_nofree();
	}
	*ac = count_split_args(*split_args);
	*av = *split_args;
	*split_used = 1;
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
	handle_single_argument(&ac, &av, &split_args, &split_used);
	validate_and_initialize(ac, av, &stack_a);
	sorting(&stack_a, &stack_b);
	cleanup_resources(stack_a, stack_b, split_args, split_used);
	return (0);
}
