#include "libft.h"
#include <stdlib.h>

 char * ft_strdup(const char *s1)
 {
    size_t  length;

    length = ft_strlen(s1);
   
    size_t i;
    i = 0; 
   char * ptr = (char *)malloc(length +1);
   if (ptr == NULL)
    return NULL;

   char *str = (char *)s1; 
   while(str[i])
   {
    ptr[i] = str[i];
    i++;
   }
    ptr[i] = '\0';
   return ptr;
 }

/*
could also do it with 
return ((char *)ft_memcpy(dup, s, len))
*/
/*
 #include <stdio.h>

int main() {
    const char *original = "Hello, World!";
    char *duplicate = ft_strdup(original);

    if (duplicate == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1; 
    }

    printf("Original: %s\n", original);
    printf("Duplicate: %s\n", duplicate);

 
    free(duplicate);

    return 0; 
}
*/