/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:52:15 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/12 19:27:11 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//#include <stdio.h>
// #include <limits.h>

static int	ft_printhex_digit(int big, unsigned long digit, int fd)
{
	char hex_char;

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
	return ft_putchar_fd(hex_char, fd);
}

static int	ft_printhex_recursive(int big, unsigned long nbr, int fd)
{
	int count;
	int error_check;

	count = 0;
	if (nbr > 15)
	{
		error_check = ft_printhex_recursive(big, nbr / 16, fd);
		if (error_check == -1)
			return -1;
		count += error_check;
	}
	error_check = ft_printhex_digit(big, nbr % 16, fd);
	if (error_check == -1)
		return -1;

	return count + 1;
	
}

int	ft_printptr(unsigned long ptr_value, int fd)
{
	int error_check;
	int count;

	count = 0;
	error_check = ft_putchar_fd('0', fd);
	if (error_check == -1)
		return -1;
	
	error_check = ft_putchar_fd('x', fd);
	if (error_check == -1)
		return -1;

	error_check = ft_printhex_recursive(0, ptr_value, fd);
	if (error_check == -1)
		return -1;
	count += error_check +2 ;

	return count;
}

 

// int main(void) {
   
//     printf("real: %p\n", (void *)"");
//     ft_printptr((unsigned long)"", 1);
//     printf("\n");

//     printf("real: %p\n", (void *)NULL);
//     ft_printptr((unsigned long)NULL, 1);
//     printf("\n");

//     printf("real: %p\n", (void *)(-14523));
//     ft_printptr((unsigned long)(-14523), 1);
//     printf("\n");

//     printf("real: %p\n", (void *)ULONG_MAX);
//     ft_printptr((unsigned long)ULONG_MAX, 1);
//     printf("\n");

//     // printf("real: %p\n", (void *)(LONG_MAX + 423856));
//     // ft_printptr((unsigned long)(LONG_MAX + 423856), 1);
//     // printf("\n");

//     return 0;
// }

// int	main(void)
// {
// 	
	//  printf("real: %p\n", (void *)3078666666666666666);
    // ft_printptr(3078666666666666666, 1);
	//     printf("\n");
    // printf("real: %p\n", NULL);
    // ft_printptr((unsigned long)NULL, 1);
	//  printf("\n");
    // printf("realptr: %p\n", (void *)-14523);
    // ft_printptr((unsigned long)(-14523), 1);
    // return 0;
// }


// ou need to ensure that the pointer value is treated as an unsigned long and
//  printed in hexadecimal format prefixed with 0x.

// Handling NULL Pointers: When the pointer is NULL, 
// it should be represented as 0x0.

// Negative Pointer Values: Pointers should not be negative. 
// If you are passing a negative value, it should be treated as an unsigned long.

// Hexadecimal Formatting: Ensure that the hexadecimal representation is 
// correctly formatted, including leading zeros if necessary.

// ointers should be treated as unsigned values when printed in hexadecimal format.
// This ensures that negative values are not incorrectly represented. By casting 
// the pointer to unsigned long, we can safely handle the pointer value without
//  worrying about sign issues.
// c

// printf("printhexrecursive count=%i\n", count);
//	printf("printhexrecursivefinal count=%i\n", count);
	//printf("ptrfinal count =%i\n", count);