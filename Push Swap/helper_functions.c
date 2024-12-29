/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:49 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/26 01:10:19 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_arr(int ac, char **av)
{
	int	i;

	(void)ac;
	i = 0;
	while (av[i])
		free(av[i++]);
	free(av);
}

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
		{
			return (unsigned char)(*str1) - (unsigned char)(*str2);
		}
		str1++;
		str2++;
	}
	return (unsigned char)(*str1) - (unsigned char)(*str2);
}

int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}
