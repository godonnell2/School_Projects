/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:10:11 by belinore          #+#    #+#             */
/*   Updated: 2024/11/12 17:31:36 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long num)
{
	int		count;

	count = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

static char	*reverse_chars(char *string)
{
	char	tmp;
	int		len;
	int		i;

	i = 0;
	while (string[i])
		i++;
	len = i + 1;
	i = 0;
	while (i < len / 2)
	{
		tmp = string[i];
		string[i] = string[len - i - 2];
		string[len - i - 2] = tmp;
		i++;
	}
	return (string);
}

void	itoa_assign_chars(char *string, long nb, int count, int sign)
{
	int	i;

	i = 0;
	if (nb == 0)
		string[i] = '0';
	while (i < count)
	{
		string[i] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	if (sign == 1)
	{
		string[i] = '-';
		i++;
	}
	string[i] = '\0';
}

char	*ft_itoa(int n)
{
	int		sign;
	int		count;
	long	nb;
	char	*string;

	sign = 0;
	nb = n;
	if (nb < 0)
	{
		sign = 1;
		nb *= -1;
	}
	count = count_digits(nb);
	string = malloc(sizeof(char) * (count + sign + 1));
	if (string == NULL)
		return (NULL);
	itoa_assign_chars(string, nb, count, sign);
	return (reverse_chars(string));
}
