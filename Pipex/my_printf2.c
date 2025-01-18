/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 08:52:16 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/18 08:52:17 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdarg.h>
#include <unistd.h>

void	ft_printstring(char *s, int fd)
{
	if (s == NULL)
	{
		s = "(null)";
	}
	ft_putstr_fd(s, fd);
}

static void	ft_printtype(const char c, va_list *args, int fd)
{
	if (c == 'c')
		ft_printchar(va_arg(*args, int), fd);
	else if (c == 's')
		ft_printstring(va_arg(*args, char *), fd);
}

static void	handle_format(char format, va_list *args, int fd)
{
	if (ft_strchr("cdisupxX", format))
		ft_printtype(format, args, fd);
	else if (format == '%')
		ft_printchar('%', fd);
}

static void	parse_format(const char *mandatory_string, va_list *args, int fd)
{
	unsigned int	i;

	i = 0;
	while (mandatory_string[i])
	{
		if (mandatory_string[i] == '%')
		{
			i++;
			handle_format(mandatory_string[i], args, fd);
		}
		else
			ft_printchar(mandatory_string[i], fd);
		i++;
	}
}

void	ft_printf(const char *mandatory_string, ...)
{
	int		fd;
	va_list	args;

	fd = 2;
	if (mandatory_string != NULL)
		va_start(args, mandatory_string);
	parse_format(mandatory_string, &args, fd);
	va_end(args);
}
