/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:02:19 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/02 17:11:24 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*s = (const char *)src;

	if (dst == NULL && src == NULL) 
        return NULL;
	if (len == 0)
		return (dst);
	dest = (char *)dst;
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

int	main(void) {
	char src[] = "abcdefgh";
	char dst[] = "01234567";
	char dst_ft[] = "01234567";

	ft_memmove(dst_ft + 2, src + 1, 5);
	memmove(dst + 2, src + 1, 5);

	printf("%s\n", dst);
	printf("%s\n", dst_ft);

	return (0);
}
*/
