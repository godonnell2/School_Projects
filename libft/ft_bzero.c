/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:20:02 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/31 11:20:04 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
	return ;
}

/*
#include <string.h>

int	main(void)
{
	char	str[] = "Grace is g";
	int		n;

	n = 4;
	ft_bzero(str, n);
	printf("MINE:%s\n", str);
	bzero(str, n);
	printf("REAl:%s", str);
}
*/
