#include "libft.h"

void ft_putstr_fd(char *s, int fd)
{
    size_t i = 0;
    while(s[i])
    {
        ft_putchar_fd(s[i], fd);
        i++;
    }
}

/*
#include <fcntl.h>
int main () 
{
    const char *temp_filename = "test_output.txt";
    int fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }
    char *s = "GRACE";
    ft_putstr_fd(s, fd);

    return (0);
}
*/
/*
create if nonexistsent
truncate if it exists let me overwrite

check if -1 is kinda like check for null 
*/