/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:39:33 by belinore          #+#    #+#             */
/*   Updated: 2024/11/19 16:50:22 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*source;

	if (dst == NULL && src == NULL)
		return (NULL);
	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	while (n > 0)
	{
		*dest = *source;
		source++;
		dest++;
		n--;
	}
	return (dst);
}
/*
int	main(void)
{
//	char dest[10] = "Abc";
//	char *src = "Def";
	char *testdst = NULL;
	char *testsrc = NULL;
//	printf("%p\n", ft_memcpy(dest, (void*)0, 3));
//	printf("%p\n",ft_memcpy(testdst, testsrc, 3));
	memcpy(testdst, testsrc, 256);
}*/
