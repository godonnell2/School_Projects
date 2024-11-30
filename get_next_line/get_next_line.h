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

size_t ft_strlen_chr(char *str, char c);
char *str_join_buff(char *existingline, char *new_data);
char		*get_next_line(int fd);

#endif