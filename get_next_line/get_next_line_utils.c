/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:09:29 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/01 16:09:30 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strlen_chr(char *str, char c)
{
	size_t	length;

	length = 0;
	if (!str)
	{
		return (0);
	}
	while (str[length] && str[length] != c)
	{
		length++;
	}
	if (str[length] == '\n')
	{
		length++;
	}
	return (length);
}

char	*str_join_consume(char *current_line, char *new_read,
		size_t *line_length)
{
	char	*join_str;
	size_t	current_len;
	size_t	new_read_len;
	size_t	i;
	size_t	total_length;

	current_len = *line_length;
	new_read_len = ft_strlen_chr(new_read, '\n');
	*line_length += new_read_len;
	i = 0;
	join_str = malloc(current_len + new_read_len + 1);
	if (!join_str)
	{
		free(current_line);
		return (NULL);
	}
	join_str[current_len + new_read_len] = '\0';
	total_length = current_len + new_read_len;
	while (i < total_length)
	{
		if (i < current_len)
			join_str[i] = current_line[i];
		else
			join_str[i] = new_read[i - current_len];
		i++;
	}
	free(current_line);
	i = 0;
	while (new_read[new_read_len + i])
	{
		new_read[i] = new_read[new_read_len + i];
		i++;
	}
	new_read[i] = '\0';
	return (join_str);
}
