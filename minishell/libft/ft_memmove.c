/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:32:07 by belinore          #+#    #+#             */
/*   Updated: 2024/11/20 17:50:24 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source;
	unsigned char	*dest;
	size_t			i;

	if (src == NULL && dst == NULL)
		return (NULL);
	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (dest > source)
	{
		while (len > 0)
		{
			dest[len - 1] = source[len - 1];
			len--;
		}
		return (dst);
	}
	i = 0;
	while (i < len)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
/*
int	main(void)
{

	ft_memmove(((void*)0), ((void*)0), 5);

	char src[] = "ABCDEF"; // dest= "CDEF"
	char *dest = &src[2];
	ft_memmove(dest, src, 3); //dest= "ABCF"
	printf("%s\n", dest);

	int size = 128 * 1024 * 1024;
 	char *dst = (char *)malloc(sizeof(char) * size);
 	char *data = (char *)malloc(sizeof(char) * size);
 
 	memset(data, 'A', size);
 	if (!dst)
 		printf("invisible");
 	memmove(dst, data, size);
 	printf("ok");
}*/
