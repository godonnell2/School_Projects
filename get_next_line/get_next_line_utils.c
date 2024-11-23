/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:00:25 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/23 14:54:21 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

void	*free_store(char **store)
{
	free(*store);
	*store = NULL;
	return (NULL);
}

char	*ft_strchr(char *s, int c)
{
	char	chr;
	char	*str;
	int		len;

	str = (char *)s;
	chr = (char)c;
	len = ft_strlen(str);
	if (chr == '\0')
		return (str + len);
	while (*str)
	{
		if (chr == *str)
		{
			return (str);
		}
		str++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	if (str == NULL)
	{
		return (0);
	}
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_strlen(src);
	if (size == 0)
	{
		return (length);
	}
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (length);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t			total_mem;
	unsigned char	*ptr;
	size_t			i;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	total_mem = count * size;
	ptr = (unsigned char *)malloc(total_mem);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < total_mem)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
