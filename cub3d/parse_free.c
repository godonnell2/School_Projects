/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:25:57 by pviegas-          #+#    #+#             */
/*   Updated: 2025/08/26 11:56:15 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	close_and_free(char *line, int fd, t_cub_elements *cub3d, bool retu)
{
	if (line)
		free(line);
	if (fd >= 0)
		close(fd);
	if (cub3d)
		return (retu);
	return (retu);
}

void	free_cub_elements(t_cub_elements *cub3d, void *mlx_ptr)
{
	if (!cub3d)
		return ;
	if (cub3d->ceiling_color)
		free(cub3d->ceiling_color);
	if (cub3d->floor_color)
		free(cub3d->floor_color);
	if (cub3d->no_text)
		free_texture(cub3d->no_text, mlx_ptr);
	if (cub3d->so_text)
		free_texture(cub3d->so_text, mlx_ptr);
	if (cub3d->we_text)
		free_texture(cub3d->we_text, mlx_ptr);
	if (cub3d->ea_text)
		free_texture(cub3d->ea_text, mlx_ptr);
	if (cub3d->map)
		free_map(cub3d->map);
	cub3d->ceiling_color = NULL;
	cub3d->floor_color = NULL;
	cub3d->no_text = NULL;
	cub3d->so_text = NULL;
	cub3d->we_text = NULL;
	cub3d->ea_text = NULL;
	cub3d->map = NULL; 
}

	 // added this to prevent segfault??cub3d->map = NULL;
void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	free(map);
}

// im not sure we need this anymore??
void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->elem)
	{
		if (data->mlx)
			free_cub_elements(data->elem, data->mlx->mlx_ptr);
		else
			free_cub_elements(data->elem, NULL);
		free(data->elem);
		data->elem = NULL;
	}
	if (data->mlx)
	{
		if (data->mlx->win_ptr && data->mlx->mlx_ptr)
			mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win_ptr);
		if (data->mlx->mlx_ptr)
		{
			mlx_destroy_display(data->mlx->mlx_ptr);
			free(data->mlx->mlx_ptr);
		}
		free(data->mlx);
	}
	free(data);
}
