/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:02:19 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/31 11:02:22 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*s = (const char *)src;

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
	return (dest);
}

/*
NEED TO REMEMBER  LEN == 0
if dest comes after src theres overlap, will overwrite src
ie if its bigger!
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
