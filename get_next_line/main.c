/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:22:02 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/01 16:22:03 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd;
	int		max;
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	fd = 0;
	max = 25;
	line = get_next_line(fd);
	while (line)
	{
		if (!--max)
		{
			printf("Max iterations reached\n");
			break ;
		}
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("get_next_line found a NULL\n");
			break ;
		}
		printf("RESULT RETURNED:'%s'\n", line);
		free(line);
	}
}
