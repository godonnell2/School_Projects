/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:00:25 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/28 10:23:38 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

void *free_store_value(t_store *store)
{
	free(store->value);
	store->value = NULL;
	store->capacity = 0;
	return (NULL);
}

static void grow_store(t_store *store)
{
	char *tmp_store_value;
	size_t i;
	size_t size_to_copy;

	size_to_copy = store->capacity;
	tmp_store_value = store->value;
	store->capacity *= 2;
	store->value = malloc(store->capacity);
	if (store->value == NULL)
	{
		free(tmp_store_value);
		store->capacity = 0;
		return;
	}
	i = 0;
	while (i < store->capacity)
	{
		if (i < size_to_copy)
			store->value[i] = tmp_store_value[i];
		else
			store->value[i] = 0;
		i++;
	}
	free(tmp_store_value);
}

static char *get_stored_line(t_store *store)
{
	size_t line_length;
	char *line;
	char *newline_pos;
	size_t i;

	newline_pos = store->value;
	while (*newline_pos && *newline_pos != '\n')
		newline_pos++;
	if (*newline_pos != '\n')
		return (NULL);
	line_length = newline_pos - store->value + 1;
	line = malloc(line_length + 1);
	if (!line)
		return (free_store_value(store));
	i = 0;
	while (store->value[i])
	{
		if (i++ < line_length)
			line[i - 1] = store->value[i - 1];
		else
			store->value[i - 1 - line_length] = store->value[i - 1];
	}
	store->value[i - line_length] = '\0';
	line[line_length] = '\0';
	return (line);
}

static char *handle_finalread(int bytes_read, size_t current_len,
							  t_store *store)
{
	char *line;
	size_t i;

	line = NULL;
	i = 0;
	if (bytes_read == 0 && current_len > 0)
	{
		line = malloc(current_len + 1);
		if (!line)
			return (free_store_value(store));
		while (i < current_len)
		{
			line[i] = store->value[i];
			i++;
		}
		line[i] = '\0';
	}
	free_store_value(store);
	return (line);
}

char *get_next_line_store(int fd, t_store *store)
{
	int bytes_read;
	size_t current_len;
	char *stored_line;

	current_len = 0;
	while (1)
	{
		stored_line = get_stored_line(store);
		if (stored_line || store->value == NULL)
			return (stored_line);
		while (store->value[current_len] != '\0')
			current_len++;
		if (current_len + BUFFER_SIZE >= store->capacity)
		{
			grow_store(store);
			if (store->value == NULL)
				return (NULL);
		}
		bytes_read = read(fd, store->value + current_len, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (handle_finalread(bytes_read, current_len, store));
		store->value[current_len + bytes_read] = '\0';
	}
}
// char	*ft_strchr(char *s, int c)
// {
// 	char	chr;
// 	char	*str;

// 	str = (char *)s;
// 	chr = (char)c;
// 	while (*str)
// 	{
// 		if (chr == *str)
// 		{
// 			return (str);
// 		}
// 		str++;
// 	}
// 	return (NULL);
// }

// void	ft_strlcpy(char *dst, const char *src, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < size - 1 && src[i])
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// }
