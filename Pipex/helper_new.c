/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:01:48 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/29 17:56:31 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_usage(void)
{
	ft_putstr_fd("Usage ./prog infile cmd1 cmd2 outfile\n", 2);
	exit(EXIT_FAILURE);
}

/*
his function takes a double pointer to t_data as an argument.
The double pointer allows the function to modify the pointer in the calling fn,
 effectively returning the allocated and initialized structure.
 */
void	init_data(t_data **tmp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->cmd = NULL;
	data->args_cmds = NULL;
	data->input_fd = -1;
	data->output_fd = -1;
	*tmp = data;
}

void	err_case(const char *msg, t_data *data)
{
	perror(msg);
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
		free(data);
	}
	exit(EXIT_FAILURE);
}
