/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 01:09:08 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/26 01:23:02 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	parse_sign_and_whitespace(const char **str, int *sign)
{
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
	{
		(*str)++;
	}
	if (**str == '-')
	{
		*sign = -1;
		(*str)++;
	}
	else if (**str == '+')
	{
		(*str)++;
	}
}

long	convert_to_long(const char *str, int sign)
{
	long	result;
	int		digit;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (sign == 1)
			return (LONG_MAX);
		else
			return (LONG_MIN);
		result = result * 10 + digit;
		str++;
	}
	return (result * sign);
}

long	ft_atol(const char *str)
{
	int	sign;

	sign = 1;
	parse_sign_and_whitespace(&str, &sign);
	return (convert_to_long(str, sign));
}

char	*allocate_and_fill_word(char **str)
{
	char	*word;
	int		k;

	word = malloc(1000);
	if (!word)
		return (NULL);
	k = 0;
	while (**str > 32)
	{
		word[k++] = **str;
		(*str)++;
	}
	word[k] = '\0';
	return (word);
}

char	**ft_split(char *str)
{
	char	**arr;
	int		j;

	j = 0;
	arr = malloc(1000 * sizeof(char *));
	if (!arr)
		return (NULL);
	while (*str)
	{
		if (*str > 32)
		{
			arr[j] = allocate_and_fill_word(&str);
			j++;
		}
		else
			str++;
	}
	arr[j] = NULL;
	return (arr);
}
