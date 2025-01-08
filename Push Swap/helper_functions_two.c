/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 01:09:08 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/08 17:27:22 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static long convert_to_long(const char *str, int sign)
{
    long result = 0;
    int digit;

    while (*str >= '0' && *str <= '9')
    {
        digit = *str - '0';

        // Check for overflow
        if (result > (LONG_MAX - digit) / 10)
        {
            return (sign == 1) ? LONG_MAX : LONG_MIN; // Return overflow value
        }

        result = result * 10 + digit;
        str++;
    }
    return result * sign;
}


long	ft_atol(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	parse_sign_and_whitespace(&str, &sign);
	result = convert_to_long(str, sign);

	// Check for overflow in `convert_to_long`
	if (result == LONG_MAX || result == LONG_MIN)
		return (result);

   return result;
}


static char	*allocate_and_fill_word(char **str, char delimiter)
{
	char	*word;
	int		k;

	word = malloc(1000); // Allocate memory for a single word
	if (!word)
		return (NULL);
	k = 0;
	while (**str && **str != delimiter) // Stop at the delimiter or end of the string
	{
		word[k++] = **str;
		(*str)++;
	}
	word[k] = '\0'; // Null-terminate the word
	return (word);
}

char	**ft_split(char *str, char delimiter)
{
	char	**arr;
	int		j;

	j = 1;
	arr = malloc(1000 * sizeof(char *)); // Allocate memory for the array of words
	if (!arr)
		return (NULL);
	arr[0] = allocate_and_fill_word((char**)&" ", ' ');
	while (*str)
	{
		if (*str != delimiter) // Check if current character is not the delimiter
		{
			arr[j] = allocate_and_fill_word(&str, delimiter); // Extract a word
			j++;
		}
		else
			str++; // Skip delimiter
	}
	arr[j] = NULL; // Null-terminate the array of words
	return (arr);
}