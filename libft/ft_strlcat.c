#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	length_src;
	size_t	length_dst;

	i = 0;
	j = 0;
	length_src = ft_strlen(src);
	length_dst = ft_strlen(dst);
	// size is a buffer to hold the output of hte cat so if its too small the cat
	// cant work
	if (size <= length_dst)
	{
		// ie you return what you would have made if you could have catted
		return (length_src + size);
	}
	i = length_dst;
	while (i < size - 1 && src[j])
	{
		dst[i++] = src[j++];
	}
	dst[i] = '\0';
	return (length_dst + length_src);
}

/*
The	strlcpy(void) and strlcat() functions return the total length of the string
 they tried to create. For  strlcat() that means the initial length of dst
 plus the length of src.
  however, that if strlcat() traverses size characters without finding a NUL,
  the length of the string is considered to be size and the destination
  string will not be NUL-terminated
Breakdown of the Condition

   Understanding length_dst:
		length_dst is the length of the existing string in dst before any concatenation occurs. This is calculated using ft_strlen(dst).

   Understanding size:
		size is the total size of the buffer allocated for dst. This includes space for the existing characters in dst and any additional characters from src,
			plus one extra byte for the null terminator ('\0').

   Condition Check:
		The condition if (size <= length_dst) checks whether the size of the buffer is less than or equal to the length of the existing string in dst.
		If this condition is true,
			it means that there is no space in the dst buffer to add any characters from src without exceeding the allocated size.

	*/