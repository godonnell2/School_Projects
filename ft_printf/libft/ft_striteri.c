/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:23:01 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/04 12:23:04 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}

/*
void	ft_putchar_wrapper(unsigned int index, char *c)
{
	int	fd;

	(void) index;
	fd = 1;
	ft_putchar_fd(*c, fd);
}
int	main(void)
{
	char	*s;

	s = "grace";
	ft_striteri(s, (ft_putchar_wrapper));
	return (0);
}
*/
