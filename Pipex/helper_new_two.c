/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_new_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:47:30 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/18 19:47:31 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	init_data(void)
{
	t_data	data;

	data.input_fd = -1;
	data.output_fd = -1;
	return (data);
}

char	*cat_strs_char(char *dest, const char *src1, char c, const char *src2)
{
	size_t	i;

	i = 0;
	if (!src1 || !src2)
	{
		return (NULL);
	}
	while (*src1)
	{
		dest[i++] = *src1++;
	}
	dest[i++] = c;
	while (*src2)
	{
		dest[i++] = *src2++;
	}
	dest[i] = '\0';
	return (dest);
}
