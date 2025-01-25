/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:42:46 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/25 06:47:33 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdarg.h>
#include <unistd.h>

static int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

void	ft_printchar(char c, int fd)
{
	ft_putchar_fd(c, fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

static size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
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
