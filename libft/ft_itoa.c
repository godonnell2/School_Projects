/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:41:04 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/03 19:44:21 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_len(long n)
{
	long	len;

	len = 0;
	if (n == 0)
		return 1;
	if (n < 0)
		{
			len = 1;
			n = -1 *n;
		}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long			nbr;
	unsigned int	len;
	char			*result;
	nbr = (long)n; 
	
	len = find_len(nbr);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if(result == NULL) 
		return (NULL);
	result[len] = '\0';
	if (nbr == 0)
		result[0] = '0';
	if (nbr < 0)
		{
			result[0] = '-';
			nbr = -1 * nbr;
		}
	while(nbr > 0)
	{
		result[--len] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (result);
}

/*
int	main(void)
{
	char	*str;

	int		numbers[] = {0, 42, -42, 123456, -10004, -2147483648};

	for (int i = 0; i < 6; i++)
	{
		
	str = ft_itoa(numbers[i]);
		printf("ft_itoa(%d) = \"%s\"\n", numbers[i], str);
		free(str); 
		
	}
	return (0);
}
*/

/*
need to add null byte after checking null 
cos otherwise you len is zero by teh time you add it
needto fill arr from len -1 or will get seg fault
becayse arrays are 0indexed 
*/

/*
int len;
len = find_len(numbers[i]);
		printf("ft_itoa(%d) = \"%d\"\n", numbers[i], len);
		*/