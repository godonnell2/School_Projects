/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:22:01 by pviegas-          #+#    #+#             */
/*   Updated: 2025/07/29 14:18:29 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//hrmm we might still need these fns i didnt account for this yet

 int	handle_close(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		free_all(data);
		exit(0);
	}
	else
		handle_movement(data);
	render_frame(data); // redraw after movement
	return (0);
}

int	game_loop(t_data *data)
{
	handle_movement(data);
	render_frame(data);
	return (0);
}

//so i need to troubleshoto there's a disconnect int he way he's initing the mlx not initing the img_ptr

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->elem = NULL;
	data->mlx = NULL;
	if (data_init(argc, argv, data) != 0)
	{
		free_all(data); 
	return (0);
		return (1);
	}
	render_frame(data); 

	// Add both hooks
	mlx_hook(data->mlx->win_ptr, 2, 1L << 0, handle_key, data);
	mlx_hook(data->mlx->win_ptr, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->mlx->win_ptr, 17, 0, handle_close, data);

	// game loop: handles movement and render
	mlx_loop_hook(data->mlx->mlx_ptr, game_loop, data);

	mlx_loop(data->mlx->mlx_ptr);
	return (0);
}


