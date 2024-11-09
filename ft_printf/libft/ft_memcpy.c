/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:21:39 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/07 19:59:41 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*d;

	i = 0;
	if (dest == src)
		return (dest);
	str = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (i < n)
	{
		d[i] = str[i];
		i++;
	}
	return (dest);
}

/*
int main()
{
	char *dest = NULL;
	char *test = NULL;
	char *src = NULL;
	size_t n = 3;
	printf("%d\n", ft_memcpy(dest, src, n));
}
*/
/*
shouldnt do until end of string for byte wiseoperations duh
no until str[i]
have to use unsigned char!! otherwise mistakes with ints

 function does not handle the case where both the source and
  destination pointers are NULL correctly, particularly when
   a non-zero size is specified. In C, dereferencing a NULL pointer
	leads to undefined behavior, which often results in a crash (e.g.,
	segmentation fault).
	SET_EXPLANATION("your memcpy does not behave well with NULL 
	as both params with size");
	its just a pointer to an address and it will fill ffrom that pt
	SANDBOX_RAISE(
			ft_memcpy(NULL, NULL, 3);

this is to deal with scenario when both are null 

*/
