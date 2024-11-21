#include "get_next_line.h"

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
