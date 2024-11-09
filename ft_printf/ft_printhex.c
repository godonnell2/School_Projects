/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:35:25 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/09 20:33:55 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	ft_printhex(long nbr, int fd)
{
   	size_t	count;
    char	minus;
	char	digit;
    	minus = '-';
if (nbr < 0)
	{
		count++;
		nbr = nbr * -1;
		ft_putchar_fd(minus, fd);
	}
if ( nbr > 15)
{  
    count += ft_printhex(nbr / 16, fd);
}
digit = (nbr % 16);
if( digit > 9 )
{  
    char hexarr[] = {'a','b','c','d','e','f'};
    ft_putchar_fd(hexarr[digit-10],fd);
}
else 
{
    digit = digit + '0';
    ft_putchar_fd(digit, fd);
}

return(count); 

}


int main()
{
    ft_printhex(16, 1);
}

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