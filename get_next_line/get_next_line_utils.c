/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:09:29 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/01 19:33:43 by gro-donn         ###   ########.fr       */
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

char	*str_join(const char *current_line, const char *new_read,
		size_t current_len, size_t new_read_len)
{
	char	*join_str;
	size_t	total_length;
	size_t	i;

	total_length = current_len + new_read_len;
	join_str = malloc(total_length + 1);
	if (!join_str)
		return (NULL);
	i = 0;
	while (i < total_length)
	{
		if (i < current_len)
			join_str[i] = current_line[i];
		else
			join_str[i] = new_read[i - current_len];
		i++;
	}
	join_str[total_length] = '\0';
	return (join_str);
}

void	consume_new_read(char *new_read, size_t new_read_len)
{
	size_t	i;

	i = 0;
	while (new_read[new_read_len + i])
	{
		new_read[i] = new_read[new_read_len + i];
		i++;
	}
	new_read[i] = '\0';
}

char	*str_join_consume(char *current_line, char *new_read,
		size_t *line_length)
{
	size_t	current_len;
	size_t	new_read_len;
	char	*join_str;
	
	current_len = *line_length;
	new_read_len = ft_strlen_chr(new_read, '\n');
	join_str = str_join(current_line, new_read, current_len, new_read_len);
	if (!join_str)
	{
		free(current_line);
		return (NULL);
	}
	*line_length += new_read_len;
	consume_new_read(new_read, new_read_len);
	free(current_line);
	return (join_str);
}
