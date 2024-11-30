#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# if BUFFER_SIZE < 1
#  error BUFFER_SIZE has to be >0
# endif

size_t		ft_strlen(const char *str);
char		*ft_strjoin(const char *s1, const char *s2);
void		*ft_memmove(void *dst, const void *src, size_t len);


typedef struct t_store
{
	char	value[BUFFER_SIZE];
	size_t	bytes_stored;
}			t_store;

char		*get_next_line(int fd);

#endif