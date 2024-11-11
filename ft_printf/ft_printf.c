/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:54:20 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/11 09:31:23 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_findtype(const char c, va_list *args)
{
	int	nbr_c;
	int	fd;
	int	big;

	big = 0;
	fd = 1;
	nbr_c = 0;
	if (c == 'c')
		nbr_c += ft_printchar(va_arg(*args, int), fd);
	else if (c == 'd' || c == 'i')
		nbr_c += ft_printlong(va_arg(*args, int), fd);
	else if (c == 's')
		nbr_c += ft_printstring(va_arg(*args, char *), fd);
	else if (c == 'u')
		nbr_c += ft_printlong(va_arg(*args, unsigned int), fd);
	else if (c == 'x' || c == 'X')
	{
		if (c == 'X')
			big = 1;
		nbr_c += ft_printhex(big, va_arg(*args, unsigned int), fd);
	}
	else if (c == 'p')
		 {
			 nbr_c += ft_printptr((unsigned long)va_arg(*args, void *), fd);
		 }
	return (nbr_c);
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
			if (ft_strchr("cdisupxX", mandatory_string[i]))
				type = type + ft_findtype(mandatory_string[i], &args);
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

//#include <stdio.h>

// int	main(void)
// {
// 	int		nr;
// 	char	*s;

// 	nr = 71;
// 	s = "grace";
// 	ft_printf("Hello '%x'\n", 0xff);
// 	// ft_printf("Hell %% %co%i%s, unsigned: %u signed: %d", 'g', nr, s,
// 	// 		(unsigned int)-1, -42);
// 	// printf("or double: %%");
// 	return (0);
// }

// " expected a statement "
// You probably have forgotten a closing bracket.
// u = unsigned int 
