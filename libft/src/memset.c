/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:14:15 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/28 16:14:18 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;
	char	letter;

	i = 0;
	str = (char *)s;
	letter = (char)c;
	while (str[i] && i < n)
	{
		str[i] = letter;
		i++;
	}
	return (s);
}

/*
int	main(void)
{
	int		c;
	size_t	n;
	char	s[] = "hello";

	c = 67;
	n = 4;
	ft_memset(s, c, n);
	printf("%s\n", s);
	memset(s, c, n);
	printf("%s", s);
}
*/

/*
67 = cap C
because we know the number of bytes
thats why its chars
because an array of int each int is 4bytes
each char is one byte
*/
