/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:58:40 by pviegas-          #+#    #+#             */
/*   Updated: 2025/08/10 17:14:16 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static int	load_texture(t_mlx *mlx, t_texture *texture, const char *texture_name)
{
    texture->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, texture->path,
                                            &texture->width, &texture->height);
    if (!texture->img_ptr)
    {
        ft_putstr_fd("Error: Failed to load ", 2);
        ft_putstr_fd((char *)texture_name, 2);
        ft_putstr_fd(" texture: ", 2);
        ft_putstr_fd(texture->path, 2);
        ft_putstr_fd("\n", 2);
        return (1);
    }

    texture->data = mlx_get_data_addr(texture->img_ptr,
                                      &texture->bits_per_pixel,
                                      &texture->line_length,
                                      &texture->endian);
    if (!texture->data)
    {
        ft_putstr_fd("Error: Failed to get data address for ", 2);
        ft_putstr_fd((char *)texture_name, 2);
        ft_putstr_fd(" texture\n", 2);
        return (1);
    }

    return (0);
}

int	xpm_to_img(t_cub_elements *elem, t_mlx *mlx)
{
	if (load_texture(mlx, elem->no_text, "North") != 0)
		return (1);
	if (load_texture(mlx, elem->so_text, "South") != 0)
		return (1);
	if (load_texture(mlx, elem->we_text, "West") != 0)
		return (1);
if (load_texture(mlx, elem->ea_text, "East") != 0) {
    printf("Failed to load East texture! Pointer: %p, Path: %s\n",
        (void*)elem->ea_text, elem->ea_text ? elem->ea_text->path : "NULL");
    return (1);
}
if (elem->ea_text && !elem->ea_text->data) {
    printf("East texture image is NULL after loading! Path: %s\n", elem->ea_text->path);
}
	return (0);
}
