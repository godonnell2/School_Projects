#include <unistd.h>
#include <stdio.h>

void ft_echo(char *s, int newlineflag)
{
    if (s == NULL)
    {
        return;
    }
    if (!newlineflag) //only happens with -n
    {
        printf("%s\n", s); 
    }
    else //standardoutput
    {
        printf("%s", s);
    }
}

int main()
{
    int newlineflag = 0;
    ft_echo("test", 1);
    return 0;
}