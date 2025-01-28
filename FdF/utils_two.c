/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:17:33 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 18:44:59 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_digit_or_hex(char c, int base)
{
	return ((c >= '0' && c <= '9') || (base == 16 && ((c >= 'a' && c <= 'f')
				|| (c >= 'A' && c <= 'F'))));
}

static int	get_digit_value(char c, int base)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (base == 16 && c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (base == 16 && c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

static long int	my_strtol(const char *str, char **endptr, int base)
{
	long int	result;
	int			sign;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
		{
			sign = -1;
		}
		else
		{
			sign = 1;
		}
	}
	while (is_digit_or_hex(*str, base))
	{
		result = result * base + get_digit_value(*str, base);
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}

const char	*parse_hex_color(const char *str, int *color)
{
	char	*end_ptr;

	if (str[0] == '0' && str[1] == 'x')
		str += 2;
	*color = my_strtol(str, &end_ptr, 16);
	return (end_ptr);
}
