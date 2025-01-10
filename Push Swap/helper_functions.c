/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:49 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/10 20:53:21 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_arr(int ac, char **av)
{
	int	i;

	if (!av)
		return ;
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
			return ((unsigned char)*str1 - (unsigned char)*str2);
		}
		str1++;
		str2++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
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

void	*my_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	value;
	size_t			i;

	ptr = s;
	value = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		ptr[i] = value;
		i++;
	}
	return (s);
}

void	parse_sign_and_whitespace(const char **str, int *sign)
{
	*sign = 1;
	while (**str == ' ' || **str == '\t' || **str == '\n' || **str == '\r'
		|| **str == '\v' || **str == '\f')
	{
		(*str)++;
	}
	while (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign *= -1;
		(*str)++;
	}
}
