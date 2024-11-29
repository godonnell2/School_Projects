#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd;
	int		max;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	// int fd = 0;
	max = 25;
	while (1)
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
