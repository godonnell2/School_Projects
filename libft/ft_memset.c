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
	str = (unsigned char *)s;
	letter = (unsigned char)c;
	while (i < n)
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
	int		arr[] = {1, 24, 18};
	char	s[] = "hello";
	size_t	j;

	c = 67;
	n = 2;
	j = 0;
	ft_memset(arr, c, n);
	while( j <= n )
	{
		printf("MINE:%d\n", arr[j++]);
	}
	ft_memset(s, c, n);
	printf("%s\n", s);
	memset(s, c, n);
	memset(arr, c, n);
	j= 0;
	while( j <= n )
	{
		printf("REAL:%d\n ", arr[j++]);
	}
	printf("%s", s);
}
*/

/*
67 = cap C
should use unsigned chars!! says so in man
because we know the number of bytes
thats why its chars
because an array of int each int is 4bytes
each char is one byte
*/
