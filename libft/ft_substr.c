#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    if(s == NULL ||  len == 0)
        return NULL;
    if( ft_strlen(s) < start )
       len = 0;
    if( ft_strlen(s + start) < len)
        len = ft_strlen(s + start);
   char * result = (char *)malloc(len * sizeof(char) + 1);
   if( result == NULL )
        return NULL;
  ft_strlcpy(result, s + start, len + 1);
    return result;
}

/*
int main ()
{
    const char s[] = "tests";
    int start = 3;
    size_t len = 5;

    printf("%s",ft_substr(s, start, len));
}
*/
/*
malloc means not and NULL
need to remember strlcpy oh wait no i dont can copy manually in exam
so long as null terminate 
if length of s is greater than start than cant run fn so len = 0
Example 2
String: s = "Hello"
Start Index: start = 6
Explanation:

ft_strlen(s) returns 5.
Since 5 < 6 is true, the condition executes, and len is set to 0.


*/