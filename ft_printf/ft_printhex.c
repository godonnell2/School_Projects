/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:35:25 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/10 19:04:57 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_printhex_recursive(int big, long nbr, int fd)
{
	size_t	count;
	char	digit;
	char	hex_char;

	count = 0;
	if (nbr > 15)
	{
		count += ft_printhex_recursive(big, nbr / 16, fd);
	}
	digit = nbr % 16;
	if (digit > 9)
	{
		if (big)
			hex_char = ('A' + (digit - 10));
		else
			hex_char = ('a' + (digit - 10));
		ft_putchar_fd(hex_char, fd);
		count++;
	}
	else
	{
		ft_putchar_fd(digit + '0', fd);
		count++;
	}
	return (count);
}

size_t	ft_printhex(int big, long nbr, int fd)
{
	char	minus;
	size_t	count;
	count = 0;
	minus = '-';
	if (nbr < 0)
	{
		ft_putchar_fd(minus, fd);
		count++;
		nbr = -nbr;
	}
	if (nbr == 0)
	{
		ft_putchar_fd('0', fd);
		return (count + 1);
	}
	count += ft_printhex_recursive(big, nbr, fd);
	return (count);
}

/*
int	main(void)
{
	int	count;

	count = ft_printhex(0, 10, 1);
	printf("\ncount:%d\n", count);
}
*/

//
// decimal = 2345
// 2 * 1000
// 3 * 100
// 4 * 10
// 5 * 1

// 3 digit (256)
// 2 digit (16)
// 1 st rest...

// 34
// 022

//  10 = a;
//     11 = b;
//     12 = c;
//     13 = d;
//     14 = e;
//     15 = f;

// size_t	ft_printhex(int big, long nbr, int fd)
// {
// 	size_t	count;
// 	char	minus;
// 	char	digit;
// 	char	hexarr_lower[6];
//     init_hex_arraylower(hexarr_lower);

// 	char	hexarr_upper[6];
// 	init_hex_arrayupper(hexarr_lower, hexarr_upper);

// 	count = 1;
// 	minus = '-';
// 	if (nbr < 0)
// 	{
// 		count++;
// 		nbr = nbr * -1;
// 		ft_putchar_fd(minus, fd);
// 	}
// 	if (nbr > 15)
// 	{
// 		count += ft_printhex(big, nbr / 16, fd);
// 	}
// 	digit = (nbr % 16);
// 	if (digit > 9)
// 	{
// 		if (big)
// 		{
// 			ft_putchar_fd(hexarr_upper[digit - 10], fd);
// 			count++;
// 		}
// 		else
// 		{
// 			ft_putchar_fd(hexarr_lower[digit - 10], fd);
// 			count++;
// 		}
// 	}
// 	else
// 	{
// 		ft_putchar_fd(digit + '0', fd);
// 		count++;
// 	}
// 	return (count);
// }

// size_t	ft_printhex(int big, long nbr, int fd)
// {
// 	size_t	count;
// 	char	minus;
// 	char	hexarr_lower[6];
// 	char	hexarr_upper[6];

// 	count = 0;
// 	minus = '-';
// 	init_hex_arraylower(hexarr_lower);
// 	init_hex_arrayupper(hexarr_lower, hexarr_upper);
// 	if (nbr < 0)
// 	{
// 		ft_putchar_fd(minus, fd);
// 		count++;
// 		nbr = -nbr;
// 	}
// 	if (nbr == 0)
// 	{
// 		ft_putchar_fd('0', fd);
// 		return (count + 1);
// 	}
// 	count += ft_printhex_recursive(big, nbr, fd, hexarr_lower, hexarr_upper);
// 	return (count);
// }