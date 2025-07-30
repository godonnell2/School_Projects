/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:22:24 by pviegas-          #+#    #+#             */
/*   Updated: 2025/07/29 15:53:37 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_mlx *mlx, t_cub_elements *cub3d)
{
	mlx->width = cub3d->map->width * 64;
	mlx->height = cub3d->map->height * 64;
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
	{
		ft_putstr_fd("Failed to initialize mlx\n", 2);
		return (EXIT_FAILURE);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			cub3d->map->width * 64,
			cub3d->map->height * 64,
			"Map Display");
	if (mlx->win_ptr == NULL)
	{
		ft_putstr_fd("Failed to create a new window\n", 2);
		return (EXIT_FAILURE);
	}
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->width, mlx->height);
	if (!mlx->img_ptr)
	{
		ft_putstr_fd("Failed to create image buffer\n", 2);
		return (EXIT_FAILURE);
	}
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr,
                                   &mlx->bits_per_pixel,
                                   &mlx->line_length,
                                   &mlx->endian);
	if (!mlx->img_data)
    	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	data_init(int argc, char **argv, t_data *data)
{
	data->elem = malloc(sizeof(t_cub_elements));
	if (!data->elem)
		return (1);
	data->mlx = malloc(sizeof(t_mlx));
	if (!data->mlx)
		return (1);
	data->mlx->mlx_ptr = NULL;
	data->mlx->win_ptr = NULL;
	
	if (!cub3d_parsing(argc, argv, data->elem))
	{
		ft_putstr_fd("Error: Parsing failed\n", 2);
		return (1);
	}
	if (init_mlx(data->mlx, data->elem) != 0)
	{
		ft_putstr_fd("Error: MLX initialization failed\n", 2);
		return (1);
	}
	if (!data->elem->map)
	{
		ft_putstr_fd("Error: Map not initialized\n", 2);
		return (1);
	}
	
	if (xpm_to_img(data->elem, data->mlx) != 0)
	{
		ft_putstr_fd("Error: Texture loading failed\n", 2);
		return (1);
	}

	return (0);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	return (map);
}
