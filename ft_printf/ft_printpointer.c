/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:52:15 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/11 09:07:18 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_printhex(int big, unsigned long nbr, int fd);

size_t ft_printptr(unsigned long ptr_value, int fd)
{

	ft_putchar_fd('0', fd);
	ft_putchar_fd('x', fd);
// 		if (ptr_value == NULL )
// 	 {
//     ft_putchar_fd('0', fd);
//     return 3;
// }
	return 2 + (ft_printhex(0, ptr_value, fd));
}

/*
int	main(void)
{
	 printf("real: %p\n", (void *)3078666666666666666);
    ft_printptr(3078666666666666666, 1);
	    printf("\n");
    printf("real: %p\n", NULL);
    ft_printptr((unsigned long)NULL, 1);
	 printf("\n");
    printf("realptr: %p\n", (void *)-14523);
    ft_printptr((unsigned long)(-14523), 1);
    return 0;
}
*/

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

