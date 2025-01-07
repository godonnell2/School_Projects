/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:50:59 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/07 12:00:13 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define EXIT_FAILURE 1

void	cleanup(t_stack *a, t_stack *b)
{
	free_stack(&a);
	free_stack(&b);
}


int main(int ac, char **av)
{
    t_stack *stack_a;
    t_stack *stack_b;
    char **split_args;
    int split_used;

    stack_a = NULL;
    stack_b = NULL;
    split_args = NULL;
    split_used = 0;

    if (ac < 2)
        err_case_nofree();

    if (ac == 2) // Handle single string input
    {
        split_args = ft_split(av[1], ' ');
        if (!split_args || !is_valid_split(split_args))
        {
            free_arr(ac, split_args);
            err_case_nofree();
        }

        ac = count_split_args(split_args) + 1; // Account for `av[0]`
        if (count_split_args(split_args) == 1) // Check for single value input
        {
            if (!is_numeric(split_args[0]) || !is_in_range(split_args[0]))
            {
                free_arr(ac, split_args);
                err_case_nofree();
            }
        }
        av = split_args;
        split_used = 1;
    }

    check_args(ac, av);
    stack_a = add_args_to_stack(ac, av);

    if (!check_sorting(&stack_a))
    {
        if (split_used)
            free_arr(ac, av);
        free_stack(&stack_a);
        exit(1);
    }

    sorting(&stack_a, &stack_b);
    cleanup(stack_a, stack_b);

    if (split_used)
        free_arr(ac, av);

    return (0);
}