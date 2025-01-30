/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 08:09:15 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/30 11:26:31 by gro-donn         ###   ########.fr       */
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
