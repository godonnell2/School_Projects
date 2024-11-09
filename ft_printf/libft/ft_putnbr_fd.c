/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:53:10 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/04 11:53:12 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	minus;
	char	digit;

	nbr = (long)n;
	minus = '-';
	if (nbr < 0)
	{
		nbr = nbr * -1;
		ft_putchar_fd(minus, fd);
	}
	if (nbr > 9)
	{
		ft_putnbr_fd(nbr / 10, fd);
	}
	digit = (nbr % 10) + '0';
	ft_putchar_fd(digit, fd);
}

/*
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int	n;
	int	fd;

	n = -12;
	char * filename = "test.txt";
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if( fd == -1 )
	{
		return (1);
	}
	ft_putnbr_fd(n, fd);
	close(fd);
	return (0);
}
*/
