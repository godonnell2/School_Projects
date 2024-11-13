/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printulong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:29:19 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/12 19:29:20 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printulong(unsigned long nbr, int fd)
{
	char	digit;
	int		count;
	int		error_check;

	count = 0;
	if (nbr > 9)
	{
		error_check = ft_printulong(nbr / 10, fd);
		if (error_check == -1)
		{
			return (-1);
		}
		count += error_check;
	}
	digit = (nbr % 10) + '0';
	if (ft_putchar_fd(digit, fd) == -1)
	{
		return (-1);
	}
	return (count + 1);
}
