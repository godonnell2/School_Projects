#include <unistd.h>
#include <stdio.h>
// NEED TO BE ABLE TO PRINT VARS?? NEED TO COPLETELY REDO THIS 
/*
Who handles $VAR?
The shell/parser, not echo.

Your shell should expand $VAR before passing the arguments to echo.
*/
void ft_echo(char **args)
{
    int i = 1;
    int newline = 1;

    if (args[i] && ft_strcmp(args[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }

    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }

    if (newline)
        printf("\n");
}

