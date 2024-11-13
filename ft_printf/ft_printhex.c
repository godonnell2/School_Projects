/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:35:25 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/13 11:01:31 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printhex_digit(int big, int digit, int fd)
{
	char	hex_char;

	if (digit > 9)
	{
		if (big)
			hex_char = 'A' + (digit - 10);
		else
			hex_char = 'a' + (digit - 10);
	}
	else
	{
		hex_char = digit + '0';
	}
	return (ft_putchar_fd(hex_char, fd));
}

static int	ft_printhex_recursive(int big, unsigned int nbr, int fd)
{
	int	count;
	int	error_check;

	count = 0;
	if (nbr > 15)
	{
		error_check = ft_printhex_recursive(big, nbr / 16, fd);
		if (error_check == -1)
			return (-1);
		count += error_check;
	}
	error_check = ft_printhex_digit(big, nbr % 16, fd);
	if (error_check == -1)
		return (-1);
	return (count + 1);
}

int	ft_printhex(int big, unsigned int nbr, int fd)
{
	int	error_check;
	int	count;

	error_check = 0;
	count = 0;
	if (nbr == 0)
	{
		error_check = ft_putchar_fd('0', fd);
		if (error_check == -1)
			return (-1);
		return (count + 1);
	}
	error_check = ft_printhex_recursive(big, nbr, fd);
	if (error_check == -1)
		return (-1);
	count += error_check;
	return (count);
}

// int	main(void)
// {
// 	int	count;

// 		ft_printhex(0, -10, 1);
// 	//printf("\ncount:%d\n", count);
// 		// count ft_printhex(0, -10, 1);
// 	//printf("\ncount:%d\n", count);

// 	printf("\nREAL:%x\n", -10);
// }

// ft_printhex is the main function to print nbr as hexadecimal.

// If nbr is 0, it directly prints '0' and returns 1.
// For other values,
//	it calls ft_printhex_recursive to handle the recursive 
//printing of hexadecimal digits.
// ft_printhex_recursive recursively divides nbr by 16,
//	printing each digit in hexadecimal using ft_printhex_digit.

// ft_printhex_digit prints a single hexadecimal digit using ft_putchar_fd.

// Example of Usage
// Calling ft_printhex(1, 255, fd):
// Since nbr is not 0,
//	ft_printhex_recursive will recursively convert 255 to hexadecimal,
//	printing "FF" if big is 1, or "ff" if big is 0.
// ft_printhex will return the total count of characters printed.

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

// static int	ft_printhex_recursive(int big, unsigned int nbr, int fd)
// {
// 	int	count;
// 	unsigned long	digit;
// 	char	hex_char;
// 	int error_check;

// 	error_check = 0;
// 	count = 0;
// 	if (nbr > 15)
// 	{
// 		error_check = ft_printhex_recursive(big, nbr / 16, fd);
// 		if(error_check == -1)
// 			return (-1);
// 		count += error_check;
// 	}
// 	digit = nbr % 16;
// 	if (digit > 9)
// 	{
// 		if (big)
// 			hex_char = ('A' + (digit - 10));
// 		else
// 			hex_char = ('a' + (digit - 10));
// 		error_check = ft_putchar_fd(hex_char, fd);
// 		if(error_check == -1)
// 			return (-1);
// 		count++;
// 	}
// 	else
// 	{
// 		error_check = ft_putchar_fd(digit + '0', fd);
// 		if(error_check == -1)
// 			return (-1);
// 		count++;
// 	}
// 	return (count);
// }

// int	ft_printhex(int big, unsigned int nbr, int fd)
// {
// 	int error_check = 0;
// 	int	count;
// 	count = 0;
// 	if (nbr == 0)
// 	{
// 		error_check = ft_putchar_fd('0', fd);
// 		if(error_check == -1 )
// 			return (-1);
// 		return (count + 1);
// 	}
// 	error_check = ft_printhex_recursive(big, nbr, fd);
// 	if(error_check == -1)
// 		return (-1);
// 	count += error_check;
// 	return (count);
// }