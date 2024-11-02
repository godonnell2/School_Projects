#include "libft.h"

char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
    unsigned int length = ft_strlen(s); 
    char *result = (char *)malloc(sizeof(char) * length  + 1);
    if(result == NULL)
        return NULL;
    
    int i = 0;
    while(s[i])
        {
            result[i] = f(i, s[i]);
            i++;
        }
    result[i] ='\0';
    return result;
}

/*
#include <stdio.h>
#include <stdlib.h>
char ft_toupper_wrapper(unsigned int index, char c) 
{
    (void) index;
    return (char)ft_toupper(c); 
}

int main ()
{
    char const *s = "grace";

    char *result = ft_strmapi(s, ft_toupper_wrapper);
    printf("%s", result);
    free(result);
    return 0;
}
*/