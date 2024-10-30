#include "libft.h"

char * ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    char *h;
    char *n;
    size_t i;
    size_t j;

    h = (char *)haystack;
    n = (char *)needle;
    i = 0;
    if (*needle == '\0')
        return (char *)haystack;
    while(h[i] && i < len)
    {
        j = 0;
        while( h[i + j] == n[j] && (i +j) < len )
        {
            j++;
            if ( n[j] == '\0')
                return h +i;
        }
        i++;
    }
    return NULL;
}

/*
   while( h[i + j] == n[j] && (i +j) < len )
Basic substring found within the limit.
Substring not found within the limit.
Limit shorter than the full match.
Empty substring (should return the original string).
Empty main string.
Full match if n is large enough.
Limit of zero.


*/

#include <stdio.h>
#include <string.h>
#include <assert.h>


void test_strnstr_functions() {
   
    char str1[] = "Hello, World!";
    char substr1[] = "World";
    size_t len = 12;
    assert(ft_strnstr(str1, substr1, len) == strnstr(str1, substr1, len));


    char substr2[] = "Mars";
    assert(ft_strnstr(str1, substr2, len) == strnstr(str1, substr2, len));

  
    len = 5; 
    assert(ft_strnstr(str1, substr1, len) == strnstr(str1, substr1, len));

   
    char substr3[] = "";
    len = 12;
    assert(ft_strnstr(str1, substr3, len) == strnstr(str1, substr3, len));

   
    char str2[] = "";
    char substr4[] = "Hello";
    assert(ft_strnstr(str2, substr4, len) == strnstr(str2, substr4, len));

   
    char str3[] = "Hello";
    char substr5[] = "Hello";
    len = 10;  
    assert(ft_strnstr(str3, substr5, len) == strnstr(str3, substr5, len));

   
    len = 0;
    assert(ft_strnstr(str1, substr1, len) == strnstr(str1, substr1, len));

    printf("All tests passed successfully.\n");
}

int main() {
    test_strnstr_functions();
    return 0;
}



