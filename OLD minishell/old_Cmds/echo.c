#include "minishell.h"
#include <stdio.h>
#include <unistd.h>


/*
Who handles $VAR?
The shell/parser, not echo.

Your shell should expand $VAR before passing the arguments to echo.
*/
int	ft_echo(char **args)
{
	int	i;
	int	newline;
	int exit_code; 
	i = 1;
	newline = 1;
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
		return 0;
}
