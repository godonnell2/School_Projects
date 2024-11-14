/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:02:19 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/14 16:37:15 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*s = (const char *)src;

	dest = (char *)dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (len == 0)
		return (dst);
	if (dest > s)
	{
		while (len > 0)
		{
			dest[len - 1] = s[len - 1];
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*dest++ = *s++;
			len--;
		}
	}
	return (dst);
}

/*
need for it to be len > 0 because size_t is unsigned and will skip to a huge nr
if it goes to 0 or below
NEED TO REMEMBER  LEN == 0
if dest comes after src theres overlap, will overwrite src
ie if its bigger!
NEED TO RETURN ORIGINAL PTR DST NOT DEST
Normal cases with valid pointers.
Edge cases with NULL pointers.
Overlapping memory regions. s+2 s-2
Cases where len is 0.

*/

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		size;
	void	*buff;
	char	*src;
	char	*dst;

	size = 50;
	buff = malloc(size);
	memset(buff, ' ', size);
	src = buff + 10;
	for (int i = 10; i < 20; ++i)
	{
		((char*)buff)[i] = 'A';
		((char*)buff)[i+22] = 'B';
	}
	dst = buff + 32;
	//ft_memmove(dst, src, 10);
	// memmove(dst + 2, src + 1, 5);
	for (int i = 0; i < size; ++i)
	{
		printf("%02d ", i);
	}
	printf("\nBefore\n");
	for (int i = 0; i < size; ++i)
	{
		printf(" %c ", ((char *)buff)[i]);
	}
	printf("\n");
	ft_memmove(dst, src, 10);
	printf("After\n");
	for (int i = 0; i < size; ++i)
	{
		printf(" %c ", ((char *)buff)[i]);
	}
	printf("\n");
	return (0);
}
*/