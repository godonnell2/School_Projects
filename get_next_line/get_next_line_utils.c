#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = 0;
	while (s[len] && len < n)
	{
		len++;
	}
	dup = (char *)malloc(len + 1);
	if (!dup)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}


char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len_total;
	char	*arr;
	size_t	i;
	size_t	j;

	i = 0;
    j = 0;
	if (s1 == NULL)
		len_total = ft_strlen(s2) + 1;
	else
		len_total = ft_strlen(s1) + ft_strlen(s2) + 1;
	arr = malloc(len_total * sizeof(char));
	if (!arr)
		return (NULL);
	if (s1)
		while (s1[i])
		{
			arr[i] = s1[i];
			i++;
		}
	while (s2[j])
	{
		arr[i + j] = s2[j];
		j++;
	}
	arr[i + j] = '\0';
	return (arr);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *dest;
	const char *s = (const char *)src;

	dest = (char *)dst;
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