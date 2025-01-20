/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:01:48 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/20 21:16:05 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_usage(void)
{
	write(2, "Usage ./prog infile cmd1 cmd2 outfile\n", 39);
	exit(1);
}

void	err_case_cmd(t_data *data, char **av, int i)
{
	ft_printf("%s: %s: command not found\n", av[0], av[i]);
	close_data(data);
	exit(1);
}

void	err_case_perror(t_data *data, char **av, int i)
{
	ft_printf("%s: %s: ", av[0], av[i]);
	perror("");
	close_data(data);
	exit(1);
}

// perror prints the most recent system error
void	err_case(t_data *data, char **av)
{
	ft_printf("%s: ", av[0]);
	perror("");
	close_data(data);
	exit(1);
}
