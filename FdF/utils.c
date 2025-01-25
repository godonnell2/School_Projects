/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 08:09:15 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/25 08:17:02 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*skip_whitespace(char *buffer)
{
	while (*buffer == ' ' || *buffer == '\n')
		buffer++;
	return (buffer);
}

char	*parse_number(char *buffer, long *value)
{
	*value = atol(buffer);
	while (*buffer != ' ' && *buffer != '\n' && *buffer != '\0')
		buffer++;
	return (buffer);
}
