#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

#include <string.h>

int	main(void)
{
	char	str[] = "Grace is g";
	int		n;

	n = 4;
	ft_btzero(str, n);
	printf("MINE:%s\n", str);
	btzero(str, n);
	printf("REAl:%s", str);
}
