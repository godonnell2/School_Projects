/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:00:25 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/22 11:50:46 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>


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

char	*ft_strdup(const char *s1)
{
	size_t	length;
	size_t	i;
	char	*ptr;
	char	*str;
  if (s1 == NULL) {
        return NULL; // Handle NULL input
    }
	length = ft_strlen(s1);
	i = 0;
	ptr = (char *)malloc(length + 1);
	if (ptr == NULL)
		return (NULL);
	str = (char *)s1;
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
    if (str == NULL)
   {return 0;
   }
	int	i;

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

// void	ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*str;
// 	size_t			i;

// 	str = (unsigned char *)s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		str[i] = 0;
// 		i++;
// 	}
// 	return ;
// }

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_mem;
	unsigned char *ptr;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	total_mem = count * size;
	ptr = (unsigned char*)malloc(total_mem);
	if (ptr == NULL)
		return (NULL);
    size_t i;
    i = 0;
	while (i < total_mem)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *dest;
	const char *s = (const char *)src;

	dest = (char *)dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (len == 0)
		return (dst);
	if (dest > s)
	{
		while (len > 0)
		{
			dest[len - 1] = s[len - 1];
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*dest++ = *s++;
			len--;
		}
	}
	return (dst);
}