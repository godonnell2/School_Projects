/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:26:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/13 09:06:32 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//# include "fdf.h"

# include <mlx.h>

/*
int	error(char *error_message)
{
	ft_printf("%s\n", error_message);
	exit (1);
}
*/
#include <stdio.h>
int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 520, 380, "Hello world!");
	if(mlx_win)
	{
		printf("hello\n");
	}
	mlx_loop(mlx);
}