#include "get_next_line.h"

int	main(void)
{
	char	*line;
	size_t	fd;
	int		max;

	fd = open("test.txt", O_RDONLY);
	max = 25;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("get line returned null\n");
			break ;
		}
		if (!--max)
		{
			printf("max value reached\n");
			break ;
		}
		printf("RESULT RETURNED:'%s'\n", line);
		free(line);
	}
	return (0);
}


// int main(void)
// {
// 	int fd = open("test.txt", O_RDONLY); // Open a test file in read-only mode
// 	if (fd < 0)
// 	{
// 		printf("Failed to open file");
// 		return 1;
// 	}

// 	char *line;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}

// 	close(fd);
// 	return 0;
// }
