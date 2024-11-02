#include "libft.h"

void ft_striteri(char *s, void (*f)(unsigned int, char*))
{
    int i = 0;
    while(s[i])
    {
        f(i, s + i);
        i++;
    }
}

/*
void ft_putchar_wrapper(unsigned int index, char *c)
{
    (void) index;
    int fd = 1;
    ft_putchar_fd(*c, fd);
}
int main()
{
    char *s = "grace";
    
    ft_striteri(s, (ft_putchar_wrapper));
    return 0;
}
*/