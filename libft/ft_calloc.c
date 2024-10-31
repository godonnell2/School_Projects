#include "libft.h"
#include <stdlib.h>

void *ft_calloc(size_t count, size_t size)
{
   size_t total_mem = count * size;

    void *ptr;

    ptr = malloc(total_mem);
    if (ptr == NULL)
        return NULL;
    
    ft_bzero(ptr, total_mem);
    return ptr;

}

/* HAVE TO REMEMEMVER TO BZERO FOR CALLOC 
if you have a count and you have size easy to malloc
but must remember null 
and need to return a ptr it s just a void ptr !! */

/*
#include <stdio.h>
#include <stdlib.h>

void *ft_calloc(size_t count, size_t size);

int main() {
    size_t count = 5; // Number of elements
    size_t size = sizeof(int); // Size of each element (int)

    // Allocate memory for an array of 5 integers
    int *array = (int *)ft_calloc(count, size);
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1; // Exit with error code
    }
}
*/