/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 01:09:08 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/09 07:21:50 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Check for overflow
// Return overflow value

static long	convert_to_long(const char *str, int sign)
{
	long	result;
	int		digit;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result > (LONG_MAX - digit) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * 10 + digit;
		str++;
	}
	return (result * sign);
}

// Check for overflow in `convert_to_long`
long	ft_atol(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	parse_sign_and_whitespace(&str, &sign);
	result = convert_to_long(str, sign);
	if (result == LONG_MAX || result == LONG_MIN)
		return (result);
	return (result);
}

static char	*allocate_and_fill_word(char **str, char delimiter)
{
	char	*word;
	int		k;

	word = malloc(1000);
	if (!word)
		return (NULL);
	k = 0;
	while (**str && **str != delimiter)
	{
		word[k++] = **str;
		(*str)++;
	}
	word[k] = '\0';
	return (word);
}

char	**ft_split(char *str, char delimiter)
{
	char	**arr;
	int		j;

	j = 1;
	arr = malloc(1000 * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[0] = malloc(1);
	arr[0][0] = '\0';
	while (*str)
	{
		if (*str != delimiter)
		{
			arr[j] = allocate_and_fill_word(&str, delimiter);
			j++;
		}
		else
			str++;
	}
	arr[j] = NULL;
	return (arr);
}
