/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:54:20 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/23 07:33:32 by gro-donn         ###   ########.fr       */
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
	if (mandatory_string == NULL)
		return (-1);
	va_start(args, mandatory_string);
	total_chars = parse_format(mandatory_string, &args, fd);
	va_end(args);
	return (total_chars);
}

/*
#include <limits.h>
#include <stdio.h>

#define FAIL "****************** TEST FAILED *********************\n\n"

int	main(void)
{
	int		a;
	int		b;
	char	*s;

	// x tests
	printf("x tests\n");
	printf(" printf out\n%d printf length\n", a = printf("%x", 0));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 0));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", -1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", -1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", 1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", 10));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 10));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", 99));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 99));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", -101));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", -101));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x",
			INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", INT_MIN));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x",
			INT_MIN));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", UINT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x",
			UINT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x %x %x %x", INT_MAX,
			INT_MIN, 0, -42));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x %x %x %x",
			INT_MAX, INT_MIN, 0, -42));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	// X tests
	printf("X tests\n");
	printf(" printf out\n%d printf length\n", a = printf("%X", 0));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 0));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", -1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", -1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", 1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", 10));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 10));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", 99));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 99));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", -101));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", -101));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X",
			INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", INT_MIN));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X",
			INT_MIN));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", UINT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X",
			UINT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X %X %X %X", INT_MAX,
			INT_MIN, 0, -42));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X %X %X %X",
			INT_MAX, INT_MIN, 0, -42));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	// c tests
	printf("c tests\n");
	printf(" printf out\n%d printf length\n", a = printf("%c", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%c", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %c", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%c ", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%c ", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %c ", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c ", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %c", '0' - 256));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c", '0'
			- 256));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%c ", '0' + 256));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%c ", '0'
			+ 256));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %c %c %c ", '1', '2',
			'3'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c %c %c ",
			'1', '2', '3'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	// d & i tests
	printf("d & i tests\n");
	printf(" printf out\n%d printf length\n", a = printf(" %d ", -99));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ", -99));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %d ", 100));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ", 100));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %d ", INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ",
			INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %d ", INT_MIN));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ",
			INT_MIN));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %d ", UINT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ",
			UINT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %d %i %d %i",
			INT_MAX, INT_MIN, 0, -42));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d %i %d
			%i", INT_MAX, INT_MIN, 0, -42));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	{ // p tests
		printf("p tests\n");
		printf(" printf out\n%d printf length\n", a = printf(" %p ",
				(void *)-1));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
				(void *)-1));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf(" printf out\n%d printf length\n", a = printf(" %p ",
				(void *)1));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
				(void *)1));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf(" printf out\n%d printf length\n", a = printf(" %p ",
				(void *)15));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
				(void *)15));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf(" printf out\n%d printf length\n", a = printf(" %p ",
				(void *)0));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
				(void *)0));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf("p tests\n");
		printf(" printf out\n%d printf length\n", a = printf(" %p ", NULL));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
				NULL));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf(" printf out\n%d printf length\n", a = printf(" %p %p ",
				(void *)LONG_MIN, (void *)LONG_MAX));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p %p ",
				(void *)LONG_MIN, (void *)LONG_MAX));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf(" printf out\n%d printf length\n", a = printf(" %p %p ",
				(void *)INT_MIN, (void *)INT_MAX));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p %p ",
				(void *)INT_MIN, (void *)INT_MAX));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf(" printf out\n%d printf length\n", a = printf(" %p %p ",
				(void *)ULONG_MAX, (void *)-ULONG_MAX));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p %p ",
				(void *)ULONG_MAX, (void *)-ULONG_MAX));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		// s tests
		s = "this is a longer test string to test printf";
		printf("s tests\n");
		printf(" printf out\n%d printf length\n", a = printf("%s", ""));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%s",
				""));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf(" printf out\n%d printf length\n", a = printf(" %s %s ", "",
				"-"));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %s %s ",
				"", "-"));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf(" printf out\n%d printf length\n",
				a = printf(" %s %s %s %s %s",
							"\
			- ",
							"",
							"4",
							"",
							s));
		printf(" ft_printf out\n%d ft_printf length\n",
				b = ft_printf(" %s %s %s %s\
			%s",
								" - ",
								"",
								"4",
								"",
								s));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		// u tests
		printf("u tests\n");
		printf(" printf out\n%d printf length\n", a = printf(" %u ", -100));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
				-100));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf(" printf out\n%d printf length\n", a = printf(" %u ", INT_MAX));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
				INT_MAX));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf(" printf out\n%d printf length\n", a = printf(" %u ", INT_MIN));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
				INT_MIN));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		printf(" printf out\n%d printf length\n", a = printf(" %u ", UINT_MAX));
		printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
				UINT_MAX));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
		// mix tests
		printf("mix tests\n");
		printf(" printf out\n%d printf length\n",
				a = printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%\
			%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%\
			%c%%",
							'A',
							"42",
							42,
							42,
							42,
							42,
							42,
							'B',
							"-42",
							-42,
							-42,
							-42,
							-42,
							42,
							'C',
							"0",
							0,
							0,
							0,
							0,
							42,
							0));
		printf(" ft_printf out\n%d ft_printf length\n",
				b = ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%\
			%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%\
			%c%%",
								'A',
								"42",
								42,
								42,
								42,
								42,
								42,
								'B',
								"-42",
								-42,
								-42,
								-42,
								-42,
								42,
								'C',
								"0",
								0,
								0,
								0,
								0,
								42,
								0));
		a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	}
}
*/

/*
#include <stdio.h>
int main()
{
	printf(NULL);
	ft_printf(NULL);
}
*/

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
