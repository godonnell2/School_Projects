/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:09:29 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/02 11:22:58 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static size_t	ft_strlen_chr(char *str, char c)
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

static char	*str_join(const char *current_line, const char *new_read,
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

static void	move_to_front(char *buffer, size_t move_len)
{
	size_t	i;

	i = 0;
	while (buffer[move_len + i])
	{
		buffer[i] = buffer[move_len + i];
		i++;
	}
	buffer[i] = '\0';
}

char	*strjoin_consumebuff(char *current_line, char *new_read,
		size_t *line_length)
{
	size_t	current_len;
	size_t	processed_len;
	char	*join_str;

	current_len = (*line_length);
	processed_len = ft_strlen_chr(new_read, '\n');
	join_str = str_join(current_line, new_read, current_len, processed_len);
	if (!join_str)
	{
		free(current_line);
		return (NULL);
	}
	*line_length += processed_len;
	move_to_front(new_read, processed_len);
	free(current_line);
	return (join_str);
}
