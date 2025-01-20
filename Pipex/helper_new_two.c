/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_new_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:47:30 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/20 21:52:47 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	init_data(void)
{
	t_data	data;

	data.input_fd = -1;
	data.output_fd = -1;
	data.pipe_fd[READ] = -1;
	data.pipe_fd[WRITE] = -1;
	data.pid1 = -1;
	data.pid2 = -1;
	return (data);
}

void	close_data(t_data *data)
{
	if (data)
	{
		if (data->input_fd > -1)
		{
			close(data->input_fd);
		}
		if (data->output_fd > -1)
		{
			close(data->output_fd);
		}
		if (data->pipe_fd[READ] > -1)
		{
			close(data->pipe_fd[READ]);
		}
		if (data->pipe_fd[WRITE] > -1)
		{
			close(data->pipe_fd[WRITE]);
		}
	}
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
