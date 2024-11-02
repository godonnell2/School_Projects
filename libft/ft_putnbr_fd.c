#include "libft.h"

void    ft_putnbr_fd(int n, int fd)
{
    long nbr;

    nbr = (long)n; 
    char minus = '-';

    if (nbr < 0 )
    {
        nbr = nbr * -1;
        ft_putchar_fd(minus, fd);
    }

    if(nbr > 9)
    {
        ft_putnbr_fd(nbr/10, fd);
    }
    char digit = (nbr %10) + '0';
    ft_putchar_fd(digit, fd);
}

/*
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int n = -12;
    char * filename = "test.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if( fd == -1 )
    {
        return 1;
    }
    ft_putnbr_fd(n, fd);
    close(fd);
    return (0);
}
*/