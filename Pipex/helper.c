/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 07:50:59 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/12 17:49:16 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_wordlen(s));
}

int	ft_wordlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	i = 0;
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (i < n && (cs1[i] || cs2[i]))
	{
		if (cs1[i] != cs2[i])
		{
			return (cs1[i] - cs2[i]);
		}
		i++;
	}
	return (0);
}


void *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest; 
    const unsigned char *s = (const unsigned char *)src; 

    while (n--)
    {
        *d++ = *s++; 
    }

    return dest; 
}

char	*cat_strs_char(char *dest, const char *src1, char c, const char *src2)
{
	size_t	i;

	i = 0;
	if (!src1 || !src2)
	{
		return (NULL);
	}
	while (*src1)
	{
		dest[i++] = *src1++;
	}
	dest[i++] = c;
	while (*src2)
	{
		dest[i++] = *src2++;
	}
	dest[i] = '\0';
	return (dest);
}

void ft_strcpy(char *src, char *dst)
{
	int i = 0;
	while(src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}