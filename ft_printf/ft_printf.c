/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:54:20 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/09 20:06:43 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_findtype(const char c, va_list *args)
{
	int	nbr_chars;
	int	fd;

	fd = 1;
	nbr_chars = 0;
	if (c == 'c')
		nbr_chars = nbr_chars + ft_printchar(va_arg(*args, int), fd);
	else if (c == 'd' || c == 'i')
		nbr_chars = nbr_chars + ft_printlong(va_arg(*args, int), fd);
	else if (c == 's')
		nbr_chars = nbr_chars + ft_printstring(va_arg(*args, char *), fd);
	else if (c == 'u')
		nbr_chars = nbr_chars + ft_printlong(va_arg(*args, unsigned int), fd);
	else if (c == 'x')
		nbr_chars = nbr_chars + ft_printhex(va_arg(*args, unsigned int), fd);
	return (nbr_chars);
}

int	ft_printf(const char *mandatory_string, ...)
{
	int				fd;
	va_list			args;
	unsigned int	i;
	unsigned int	type;

	type = 0;
	fd = 1;
	i = 0;
	va_start(args, mandatory_string);
	while (mandatory_string[i])
	{
		if (mandatory_string[i] == '%')
		{
			i = i + 1;
			if (ft_strchr("cdisupXX", mandatory_string[i]))
			{
				type = type + ft_findtype(mandatory_string[i], &args);
			}
			else if (mandatory_string[i] == '%')
				type = type + ft_printchar('%', fd);
		}
		else
			type = type + ft_printchar(mandatory_string[i], fd);
		i++;
	}
	va_end(args);
	return (type);
}
/*
#include <stdio.h>

int	main(void)
{
	int		nr;
	char	*s;

	nr = 71;
	s = "grace";
	//ft_printf("Hello %c", 'g');
	ft_printf("Hell %% %co%i%s, unsigned: %u signed: %d", 'g', nr, s,
			(unsigned int)-1, -42);
	// printf("or double: %%");
	return (0);
}
*/
