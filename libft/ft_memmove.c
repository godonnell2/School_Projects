#include "libft.h"

void *ft_memmove(void *dst, const void *src, size_t len) {
    if ( len == 0) 
        return dst;
    
    char *dest = (char *)dst;
    const char *s = (const char*) src;

    if (dest > s) 
    {
        while(len > 0)
        {
        dest[len -1] = s[len-1];
        len--;
        }
    }
    else
    {
        while(len > 0)
        {
        *dest++ = *s++;
        len--;
        }
    }
    return dest;
}
 
/*
NEED TO REMEMBER  LEN == 0
if dest comes after src theres overlap, will overwrite src
ie if its bigger!
#include <stdio.h> 
#include <string.h>
int main() {
    char src[] = "abcdefgh";
    char dst[] = "01234567";
    char dst_ft[] = "01234567";

    ft_memmove(dst_ft + 2, src + 1, 5);
    memmove(dst + 2, src + 1, 5);

    printf("%s\n", dst);   
    printf("%s\n", dst_ft); 

    return 0; 
}
*/