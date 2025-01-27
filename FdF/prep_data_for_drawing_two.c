/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_data_for_drawing_two.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:16:04 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/26 19:56:33 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> //NEED TO REPLACE WITH OWN

void generate_horizontal_edges(t_map *map, t_edge *edges, int *edge_index)
{
	int y;
	int x;
	int current_index;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols - 1)
		{
			current_index = y * map->cols + x;
			edges[*edge_index].start = current_index;
			edges[*edge_index].end = current_index + 1;
			(*edge_index)++;
			x++;
		}
		y++;
	}
}

void generate_vertical_edges(t_map *map, t_edge *edges, int *edge_index)
{
	int y;
	int x;
	int current_index;

	y = 0;
	while (y < map->rows - 1)
	{
		x = 0;
		while (x < map->cols)
		{
			current_index = y * map->cols + x;
			edges[*edge_index].start = current_index;
			edges[*edge_index].end = current_index + map->cols;
			(*edge_index)++;
			x++;
		}
		y++;
	}
}

void populate_edges(t_map *map, t_edge **edges, int *edges_count)
{
	int total_edges;

	total_edges = (map->cols - 1) * map->rows + (map->rows - 1) * map->cols;
	*edges = malloc(total_edges * sizeof(t_edge));
	if (*edges == NULL)
	{
		handle_error("Memory allocation failed for  populate edges.\n");
	}
	*edges_count = 0;
	generate_horizontal_edges(map, *edges, edges_count);
	generate_vertical_edges(map, *edges, edges_count);
}
