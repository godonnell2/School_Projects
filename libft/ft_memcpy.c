#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*d;

	i = 0;
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
shouldnt do until end of string for byte wiseoperations duh
no until str[i]
have to use unsigned char!! otherwise mistakes with ints
*/