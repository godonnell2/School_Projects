#include "libft.h"

void ft_putendl_fd(char *s, int fd)
{
    ft_putstr_fd(s, fd);
    ft_putchar_fd('\n', fd);
}

/*
for the close function
0644 is the permissions chmod etc...
$ IS NEWLINE
cat -e
% is NO newline
*/

/*
#include <fcntl.h>
#include <unistd.h>
int main()
{
    char *temp_filename = "test_output.txt";
    int fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); 

    if(fd == -1 )
    {
        return 1;
    }
  
    char *s = "Grace is the best";
    ft_putendl_fd(s, fd);
    close(fd);
    return 0;
}
*/

