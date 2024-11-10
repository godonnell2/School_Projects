/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:52:15 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/10 18:02:46 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// static size_t	ft_printhex_recursive(int big, long nbr, int fd)
// {
// 	size_t	count;
// 	char	digit;
// 	char	hex_char;

// 	count = 0;
// 	if (nbr > 15)
// 	{
// 		count += ft_printhex_recursive(big, nbr / 16, fd);
// 	}
// 	digit = nbr % 16;
// 	if (digit > 9)
// 	{
// 		if (big)
// 			hex_char = ('A' + (digit - 10));
// 		else
// 			hex_char = ('a' + (digit - 10));
// 		ft_putchar_fd(hex_char, fd);
// 		count++;
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
// 	char	minus;
// 	size_t	count;

// 	count = 0;
// 	minus = '-';
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
// 	count += ft_printhex_recursive(big, nbr, fd);
// 	return (count);
// }
