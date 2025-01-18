/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:01:48 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/18 19:46:29 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_usage(void)
{
	write(2, "Usage ./prog infile cmd1 cmd2 outfile\n", 39);
	exit(1);
}

static void	close_exit(t_data *data)
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
	exit(1);
}

void	err_case_cmd(t_data *data, char **av, int i)
{
	ft_printf("%s: %s: command not found\n", av[0], av[i]);
	close_exit(data);
}

void	err_case_perror(t_data *data, char **av, int i)
{
	ft_printf("%s: %s: ", av[0], av[i]);
	perror("");
	close_exit(data);
}

// perror prints the most recent system error
void	err_case(t_data *data, char **av)
{
	ft_printf("%s: ", av[0]);
	perror("");
	close_exit(data);
}
