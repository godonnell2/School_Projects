/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:00:25 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/25 19:07:20 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

void	*free_store_value(t_store *store)
{
	free(store->value);
	store->value = NULL;
	store->size = 0;
	return (NULL);
}

// char	*ft_strchr(char *s, int c)
// {
// 	char	chr;
// 	char	*str;

// 	str = (char *)s;
// 	chr = (char)c;
// 	while (*str)
// 	{
// 		if (chr == *str)
// 		{
// 			return (str);
// 		}
// 		str++;
// 	}
// 	return (NULL);
// }

void	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
