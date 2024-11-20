/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlong.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:55:07 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/19 10:36:52 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printlong(long nbr, int fd)
{
	char	digit;
	int		count;
	int		error_check;

	error_check = 0;
	count = 0;
	if (nbr < 0)
	{
		count = ft_putchar_fd('-', fd);
		if (count == -1)
			return (-1);
		nbr = nbr * -1;
	}
	if (nbr > 9)
	{
		error_check = ft_printlong(nbr / 10, fd);
		if (error_check == -1)
			return (-1);
		count += error_check;
	}
	digit = (nbr % 10) + '0';
	if (ft_putchar_fd(digit, fd) == -1)
		return (-1);
	return (count + 1);
}

/*
need to return length
need to account for zero
theres always going to be one nr
dont have to worry about zero if do >9

    Local Scope: Each call to ft_printlong has its own error_check variable,
     which is initialized to 0 at the start of that call.
    Value Propagation: When a recursive call returns, the value of error_check
     in the calling function is updated to the value returned from the 
     recursive call. This allows the calling function to accumulate the total 
     count of characters printed.
    Final Result: The final return value from the original call gives you the 
    total number of characters printed, which includes all characters
     printed in all recursive calls.

This mechanism allows the function to effectively count and print each digit of
 the number while managing recursion cleanly. Each call operates independently,
  and the values are passed back up the call stack, allowing for a cumulative
   count without resetting to zero.
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
