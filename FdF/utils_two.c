/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:17:33 by gro-donn          #+#    #+#             */
/*   Updated: 2025/02/01 11:15:41 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static float	parse_integer_part(const char **str, int *sign)
{
	float	result;

	result = 0.0f;
	if (**str == '-')
	{
		*sign = -1;
		(*str)++;
	}
	else if (**str == '+')
	{
		*sign = 1;
		(*str)++;
	}
	else
	{
		*sign = 1;
	}
	while (my_isdigit((unsigned char)**str))
	{
		result = result * 10.0f + (**str - '0');
		(*str)++;
	}
	return (result);
}

// if decimal exists, parse digits after it
// fraction keeps track of digits after decimal
// divisor tracks how many zeros to divide by eg 10, 100
static float	parse_fractional_part(const char **str)
{
	float	fraction;
	float	divisor;

	fraction = 0.0f;
	fraction = 0.0f;
	divisor = 1.0f;
	if (**str == '.')
	{
		(*str)++;
		while (my_isdigit((unsigned char)**str))
		{
			fraction = fraction * 10.0f + (**str - '0');
			divisor *= 10.0f;
			(*str)++;
		}
	}
	return (fraction / divisor);
}

// Store the pointer to the first invalid character for fruther parsing
float	my_strtof(const char *str, char **endptr)
{
	int		sign;
	float	result;

	result = parse_integer_part(&str, &sign);
	result += parse_fractional_part(&str);
	if (endptr)
	{
		*endptr = (char *)str;
	}
	return (sign * result);
}
