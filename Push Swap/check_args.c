/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:41 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/07 11:55:57 by gro-donn         ###   ########.fr       */
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

void check_args(int ac, char **av)
{
    int *nums;
    int size;
    int i;

    // Determine size based on input format
    if (ac == 2) // Single string input (split case)
        size = count_split_args(av);
    else // Multiple arguments
        size = ac - 1;

    nums = malloc(sizeof(int) * size);
    if (!nums)
        err_case_nofree(); // Handle memory allocation failure

    for (i = 0; i < size; i++)
    {
        const char *current_arg;

        // Handle single string input (split case)
        if (ac == 2)
            current_arg = av[i];
        else
            current_arg = av[i + 1];

        if (!is_numeric(current_arg)) // Check if argument is numeric
        {
            free(nums);
            err_case_nofree();
        }

        if (!is_in_range(current_arg)) // Check if argument is in range
        {
            free(nums);
            err_case_nofree();
        }

        nums[i] = ft_atol(current_arg); // Convert and store in nums array
    }

    if (has_duplicates(nums, size)) // Check for duplicates
    {
        free(nums);
        err_case_nofree();
    }

    free(nums); // Free allocated memory
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+') // Handle negative or positive signs
		i++;
	if (str[i] == '\0') // Ensure there's at least one digit
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9') // Non-numeric character
			return (0);
		i++;
	}
	return (1);
}

int	has_duplicates(int *arr, int size)
{
	int i = 0;
    
    while (i < size)
    {
        int j = i + 1; 
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

