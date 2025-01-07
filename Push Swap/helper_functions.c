/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:49 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/07 07:21:53 by gro-donn         ###   ########.fr       */
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
void parse_sign_and_whitespace(const char **str, int *sign)
{
    // Initialize sign to 1 (positive)
    *sign = 1;

    // Skip leading whitespace
    while (**str == ' ' || **str == '\t' || **str == '\n' || 
           **str == '\r' || **str == '\v' || **str == '\f') // Check for whitespace characters
    {
        (*str)++; // Move to the next character
    }

    // Check for sign
    while (**str == '+' || **str == '-') // Check for '+' or '-'
    {
        if (**str == '-') // If the character is '-'
            *sign *= -1; // Flip the sign
        (*str)++; // Move to the next character
    }
}
