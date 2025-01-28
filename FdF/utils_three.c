/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:40:21 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 18:43:45 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	parse_sign(const char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	if (**str == '+')
		(*str)++;
	return (1);
}

static float	parse_integer_part(const char **str)
{
	float	result;

	result = 0.0f;
	while (my_isdigit((unsigned char)**str))
	{
		result = result * 10.0f + (**str - '0');
		(*str)++;
	}
	return (result);
}

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

static int	parse_exponent(const char **str)
{
	int	exponent;
	int	sign;

	exponent = 0;
	sign = 1;
	if (**str == 'e' || **str == 'E')
	{
		(*str)++;
		if (**str == '-')
		{
			sign = -1;
			(*str)++;
		}
		else if (**str == '+')
		{
			(*str)++;
		}
		while (my_isdigit((unsigned char)**str))
		{
			exponent = exponent * 10 + (**str - '0');
			(*str)++;
		}
	}
	return (sign * exponent);
}

float	my_strtof(const char *str, char **endptr)
{
	int		sign;
	float	result;
	int		exponent;

	sign = parse_sign(&str);
	result = parse_integer_part(&str);
	result += parse_fractional_part(&str);
	exponent = parse_exponent(&str);
	result *= powf(10.0f, exponent);
	if (endptr)
		*endptr = (char *)str;
	return (sign * result);
}
