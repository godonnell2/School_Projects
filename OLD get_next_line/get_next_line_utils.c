/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:00:25 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/29 15:08:27 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

void *reset_store_value(t_store *store)
{
	 store->capacity = BUFFER_SIZE; 
	store->value[0] = '\0';  
	return (NULL);
}

size_t	ft_strlen(char *str, char c)
{
	size_t	counter;

	counter = 0;
	if (!str)
		return (0);
	while (str[counter] && str[counter] != c)
		counter++;
	if (str[counter] == '\n')
		counter++;
	return (counter);
}

char *str_join(t_store *store, char *s2)
{
    size_t s1_len = ft_strlen(store->value, 0);
    size_t s2_len = ft_strlen(s2, '\n');
    size_t total_len = s1_len + s2_len;

    if (total_len > store->capacity) 
        return (NULL);

    size_t i = 0;
    while (i < s2_len)
    {
        store->value[s1_len + i] = s2[i];
        i++;
    }
    store->value[s1_len + i] = '\0'; 
    return (store->value);
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
        return (NULL);

    for (i = 0; i < line_length; i++) 
        line[i] = store->value[i];

    line[line_length] = '\0'; 

  
    i = 0;
    while (store->value[line_length + i])
    {
        store->value[i] = store->value[line_length + i];
        i++;
    }
    store->value[i] = '\0';

    return line;
}

static char *handle_finalread(int bytes_read, size_t current_len, t_store *store)
{
    char *line;
    size_t i;
	line = NULL; 
	
    if (bytes_read == 0 && current_len > 0) 
        line = malloc(current_len + 1); 
        if (!line)
            return (NULL);

        i = 0;
        while (i < current_len) 
        {
            line[i] = store->value[i];
            i++;
        }
        line[i] = '\0'; 
        store->value[0] = '\0'; 
        return (line);
    }
 


char *get_next_line_store(int fd, t_store *store)
{
    int bytes_read;
    size_t current_len = 0;
    char *stored_line;

    while (1)
    {
        stored_line = get_stored_line(store);
        if (stored_line || store->value[0] == '\0')
            return stored_line;

        while (store->value[current_len])
            current_len++;

        if (current_len >= store->capacity)
            return (NULL); 

        bytes_read = read(fd, store->value + current_len, store->capacity - current_len);
        if (bytes_read <= 0)
            return handle_finalread(bytes_read, current_len, store);

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
