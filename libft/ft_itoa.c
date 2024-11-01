/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:41:04 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/01 14:41:06 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_len(int n)
{
	int	len;

	len = 0;
	if (n == 0 || n < 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	unsigned int	len;
	char			*result;

	if (n < 0)
	{
		nbr = -n;
		len = find_len(n) + 1;
	}
	else
	{
		nbr = n;
		len = find_len(n);
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	if (n < 0)
		result[0] = '-';
	while (nbr != 0)
	{
		result[len - 1] = nbr % 10 + '0';
		nbr = nbr / 10;
		len--;
	}
	if (n == 0)
		result[0] = '0';
	return (result);
}
/*
int	main(void)
{
	char	*str;
	int		numbers[] = {0, 42, -42, 123456, -123456, -2147483648};

	for (int i = 0; i < 6; i++)
	{
		str = ft_itoa(numbers[i]);
		printf("ft_itoa(%d) = \"%s\"\n", numbers[i], str);
		free(str); // Free allocated memory
	}
	return (0);
}
*/
/*needto fill arr from len -1 or will get seg fault*/