/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:00:25 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/20 18:07:43 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len_total;
	char	*arr;

	len_total = ft_strlen(s1) + ft_strlen(s2) + 1;
	arr = (char *)malloc(len_total * sizeof(char));
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, len_total);
	ft_strlcat(arr, s1, len_total);
	ft_strlcat(arr, s2, len_total);
	return (arr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	cap_length;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	cap_length = len;
	if (s_len - start < len)
		cap_length = s_len - start;
	result = (char *)ft_calloc(cap_length + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s + start, cap_length + 1);
	return (result);
}


char	*ft_strchr( char *s, int c)
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
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst,const char *src, size_t size)
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (size + src_len);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (size + src_len);
	i = 0;
	while (src[i] && dst_len + i < size - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
	return ;
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_mem;
	void	*ptr;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	total_mem = count * size;
	ptr = (void *)malloc(total_mem);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_mem);
	return (ptr);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*s = (const char *)src;

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