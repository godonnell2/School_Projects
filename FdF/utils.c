/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 08:09:15 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 18:39:45 by gro-donn         ###   ########.fr       */
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

int	my_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

// static int parse_sign(const char **str)
// {
//     if (**str == '-')
//     {
//         (*str)++;
//         return (-1);
//     }
//     if (**str == '+')
//         (*str)++;
//     return (1);
// }

// static float parse_integer_part(const char **str)
// {
//     float result = 0.0f;
//     while (my_isdigit((unsigned char)**str))
//     {
//         result = result * 10.0f + (**str - '0');
//         (*str)++;
//     }
//     return (result);
// }

// static float parse_fractional_part(const char **str)
// {
//     float fraction = 0.0f, divisor = 1.0f;
//     if (**str == '.')
//     {
//         (*str)++;
//         while (my_isdigit((unsigned char)**str))
//         {
//             fraction = fraction * 10.0f + (**str - '0');
//             divisor *= 10.0f;
//             (*str)++;
//         }
//     }
//     return (fraction / divisor);
// }

// static int parse_exponent(const char **str)
// {
//     int exponent = 0, sign = 1;
//     if (**str == 'e' || **str == 'E')
//     {
//         (*str)++;
//         if (**str == '-')
//         {
//             sign = -1;
//             (*str)++;
//         }
//         else if (**str == '+')
//         {
//             (*str)++;
//         }
//         while (my_isdigit((unsigned char)**str))
//         {
//             exponent = exponent * 10 + (**str - '0');
//             (*str)++;
//         }
//     }
//     return (sign * exponent);
// }

// static float my_strtof(const char *str, char **endptr)
// {
//     int sign = parse_sign(&str);
//     float result = parse_integer_part(&str);
//     result += parse_fractional_part(&str);
//     int exponent = parse_exponent(&str);
//     result *= powf(10.0f, exponent);

//     if (endptr)
//         *endptr = (char *)str;
//     return (sign * result);
// }
// static float	my_strtof(const char *str, char **endptr)
// {
// 	int		sign;
// 	float	result;
// 	float	fraction;
// 	float	divisor;
// 	int		exponent_sign;
// 	int		exponent;

// 	sign = 1;
// 	result = 0.0f;
// 	fraction = 0.0f;
// 	divisor = 1.0f;
// 	exponent_sign = 1;
// 	exponent = 0;
// 	if (*str == '-')
// 	{
// 		sign = -1;
// 		str++;
// 	}
// 	else if (*str == '+')
// 	{
// 		str++;
// 	}
// 	// Parse integer part
// 	while (my_isdigit((unsigned char)*str))
// 	{
// 		result = result * 10.0f + (*str - '0');
// 		str++;
// 	}
// 	// Parse fractional part
// 	if (*str == '.')
// 	{
// 		str++;
// 		while (my_isdigit((unsigned char)*str))
// 		{
// 			fraction = fraction * 10.0f + (*str - '0');
// 			divisor *= 10.0f;
// 			str++;
// 		}
// 	}
// 	result += fraction / divisor;
// 	// Parse exponent part
// 	if (*str == 'e' || *str == 'E')
// 	{
// 		str++;
// 		if (*str == '-')
// 		{
// 			exponent_sign = -1;
// 			str++;
// 		}
// 		else if (*str == '+')
// 		{
// 			str++;
// 		}
// 		while (my_isdigit((unsigned char)*str))
// 		{
// 			exponent = exponent * 10 + (*str - '0');
// 			str++;
// 		}
// 		result *= powf(10.0f, exponent_sign * exponent);
// 	}
// 	// Set endptr to point to the first unprocessed character
// 	if (endptr)
// 	{
// 		*endptr = (char *)str;
// 	}
// 	return (sign * result);
// }
// if (endptr == str) {
// return (str);  // No valid number found, return original string
// strtof() function converts a string to a float-point number
const char	*parse_number(const char *str, float *value)
{
	char	*endptr;

	*value = my_strtof(str, &endptr);
	if (endptr == str)
	{
		return (str);
	}
	str = endptr;
	str = skip_whitespace(str);
	return (str);
}
