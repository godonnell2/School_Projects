/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlong.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:55:07 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/10 18:02:46 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_printlong(long nbr, int fd)
{
	char	minus;
	char	digit;
	size_t	count;

	count = 1;
	minus = '-';
	if (nbr < 0)
	{
		count++;
		nbr = nbr * -1;
		ft_putchar_fd(minus, fd);
	}
	if (nbr > 9)
	{
		count += ft_printlong(nbr / 10, fd);
	}
	digit = (nbr % 10) + '0';
	ft_putchar_fd(digit, fd);
	return (count);
}

/*
need to return length
need to account for zero
theres always going to be one nr
dont have to worry about zero if do >9
 */

// #include <stdio.h>
// #include <limits.h>
// int main()
// {
// 	int n = 0;
// 	long numbers[] = {
// 		0, -1, INT32_MIN, INT32_MAX, INT64_MAX,
// 			(unsigned int) -1,
// 			UINT32_MAX};
// 	size_t count = sizeof(numbers) / sizeof(long);
// 	for (int i = 0; i < count; ++i)
// 	{
// 		printf("Printing \n%ld\n", numbers[i]);
// 		size_t num_chars = ft_printlong(numbers[i], 1);
// 		printf("\n");
// 	}
// }

/*
int	ft_printint(int n)
{
   int count;
	int	nbr;

	nbr = n;
	count = 1;
	if (nbr < 0 && n != -2147483648)
	{
		count++;
		nbr = nbr * -1;
	}
	while( nbr > 9)
	{
		count++;
		nbr = nbr /10;
	}
	ft_putnbr_fd(n, 1);
	if (n == -2147483648)
		return (11);
	return (count);
}
*/