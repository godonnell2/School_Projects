/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 08:09:15 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/25 18:28:30 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <limits.h>

const char	*skip_whitespace(const char *buffer)
{
	while (*buffer == ' ' || *buffer == '\n')
		buffer++;
	return (buffer);
}

static char	*check_sign_and_skip(const char **str, int *sign)
{
	*str = skip_whitespace(*str);
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign = -1;
		(*str)++;
	}
	return ((char *)*str);
}

static char	*my_atol(const char *str, long *value)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	str = check_sign_and_skip(&str, &sign);
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
		{
			if (sign == 1)
				*value = LONG_MAX;
			else
				*value = LONG_MIN;
			return ((char *)str);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	*value = result * sign;
	return ((char *)str);
}

const char *parse_number(const char *buffer, long *value)
{
    buffer = my_atol(buffer, value);
    buffer = skip_whitespace(buffer);
    return buffer;
}
