/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:54:20 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/14 10:56:13 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printtype(const char c, va_list *args, int fd)
{
	if (c == 'c')
		return (ft_printchar(va_arg(*args, int), fd));
	else if (c == 'd' || c == 'i')
		return (ft_printlong(va_arg(*args, int), fd));
	else if (c == 's')
		return (ft_printstring(va_arg(*args, char *), fd));
	else if (c == 'u')
		return (ft_printlong(va_arg(*args, unsigned int), fd));
	else if (c == 'x' || c == 'X')
		return (ft_printhex(c == 'X', va_arg(*args, unsigned int), fd));
	else if (c == 'p')
		return (ft_printptr(va_arg(*args, void *), fd));
	return (-1);
}

static int	handle_format(char format, va_list *args, int fd)
{
	if (ft_strchr("cdisupxX", format))
		return (ft_printtype(format, args, fd));
	else if (format == '%')
		return (ft_printchar('%', fd));
	return (-1);
}

static int	parse_format(const char *mandatory_string, va_list *args, int fd)
{
	unsigned int	i;
	int				printed_chars;
	int				total_chars;

	i = 0;
	printed_chars = 0;
	total_chars = 0;
	while (mandatory_string[i])
	{
		if (mandatory_string[i] == '%')
		{
			i++;
			printed_chars = handle_format(mandatory_string[i], args, fd);
		}
		else
			printed_chars = ft_printchar(mandatory_string[i], fd);
		if (printed_chars == -1)
			return (-1);
		total_chars += printed_chars;
		i++;
	}
	return (total_chars);
}

int	ft_printf(const char *mandatory_string, ...)
{
	int		fd;
	va_list	args;
	int		total_chars;

	fd = 1;
	va_start(args, mandatory_string);
	total_chars = print_format(mandatory_string, &args, fd);
	va_end(args);
	return (total_chars);
}

// here we're convering it to a ptr &args in all the otehrs were
// dealing with already as a pointer 
// int	ft_printf(const char *mandatory_string, ...)
// {
// 	int				fd;
// 	va_list			args;
// 	unsigned int	i;
// 	unsigned int	nbr_chars;
// 	int				printed_chars;

// 	nbr_chars = 0;
// 	printed_chars = 0;
// 	fd = 1;
// 	i = 0;
// 	va_start(args, mandatory_string);
// 	while (mandatory_string[i])
// 	{
// 		if (mandatory_string[i] == '%')
// 		{
// 			i++;
// 			printed_chars = handle_format(mandatory_string[i], &args,fd);
// 		}
// 		else
// 			printed_chars = ft_printchar(mandatory_string[i], fd);
// 		if (printed_chars == -1)
// 		{
// 			va_end(args);
// 			return (-1);
// 		}
// 		nbr_chars += printed_chars;
// 		i++;
// 	}
// 	va_end(args);
// 	return (nbr_chars);
// }

// int	ft_printf(const char *mandatory_string, ...)
// {
// 	int				fd;
// 	va_list			args;
// 	unsigned int	i;
// 	unsigned int	nbr_chars;
// 	int				printed_chars;

// 	nbr_chars = 0;
// 	printed_chars = 0;
// 	fd = 1;
// 	i = 0;
// 	va_start(args, mandatory_string);
// 	while (mandatory_string[i])
// 	{
// 		if (mandatory_string[i] == '%')
// 		{
// 			i++;
// 			if (ft_strchr("cdisupxX", mandatory_string[i]))
// 				printed_chars = ft_printtype(mandatory_string[i], &args, fd);
// 			else if (mandatory_string[i] == '%')
// 				printed_chars = ft_printchar('%', fd);
// 		}
// 		else
// 			printed_chars = ft_printchar(mandatory_string[i], fd);
// 		if (printed_chars == -1)
// 		{
// 			va_end(args);
// 			return (-1);
// 		}
// 		nbr_chars += printed_chars;
// 		i++;
// 	}
// 	va_end(args);
// 	return (nbr_chars);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	int		nr;
// 	char	*s;

// 	nr = 71;
// 	s = "grace";
// 	ft_printf("Hello '%x'\n", 0xff);
// 	ft_printf("mine:%c%c%c\n", 'a', '\t', 'b' );
// 	printf("real:%c%c%c\n", 'a', '\t', 'b' );
// 	ft_printf("mine:%cc%cc%c\n", 'a', '\t', 'b');
// 	printf("real:%cc%cc%c\n", 'a', '\t', 'b');

// 		ft_printf("mine:%cs%cs%c\n", 'c', 'b', 'a');
// 		printf("real:%cs%cs%c\n", 'c', 'b', 'a');
// 	// ft_printf("Hell %% %co%i%s, unsigned: %u signed: %d", 'g', nr, s,
// 	// 		(unsigned int)-1, -42);
// 	// printf("or double: %%");
// 	return (0);
// }

// " expected a statement "
// You probably have forgotten a closing bracket.
// u = unsigned int

// #define va_start(ap,param) __builtin_va_start(ap, param)
// Expands to:

// __builtin_va_start(args, mandatory_string)
// when i had it by value and not the address it was printing the wrong thing
// when I had char it was giving a WARNING that it would grow to an int
