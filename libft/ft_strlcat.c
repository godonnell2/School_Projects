/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:22:10 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/03 18:56:23 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (size + src_len);
	i = 0;
	while (src[i] && dst_len + i < size - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/*
int	main(void)
{
	char	*src;
	char	dest[20] = "test";
	src = "Olaaa";
	
	printf("My Func : %zu\n", ft_strlcat(dest, src, 6));
		printf("Resulting string: '%s'\n", dest);
	char	test[20] = "test";
		
	printf("Original : %zu\n", strlcat(test, src, 6));
		printf("Resulting string: '%s'\n", test);
	return(0);
}
*/

/*
NEED TO REMMEBER i < dst_size
dst_size == 0
*/

/*

	If dst_size is less than or equal to the length of dst, the function should
		return dst_size + ft_strlen(src),
			not just ft_strlen(src). This is because
		the destination string is not modified in that case,
			and the return value
		should reflect the total length that would have been created.

Buffer Overflow:

	The current implementation does not handle cases where dst_size is less
		or equal to the length of dst. If dst_size is 0, it should return the
		length of src without modifying dst.

 int main() {
    char dest[10] = "Hello"; // Length of "Hello" is 5
    const char *src = "World!"; // Length of "World!" is 6

   
    size_t result = strlcat(dest, src, sizeof(dest));

    printf("Resulting string: '%s'\n", dest);
    printf("Total length of the string it tried to create: %zu\n", result);
    
    return 0;
}

*/
/*
#include <stdio.h>
#include <string.h>

void	test_ft_strlcat(size_t (*fn)(char *dst, const char *src,
			size_t dst_size)) {
	char dst1[20] = "Hello, ";
	char src1[] = "World!";
	size_t result1 = fn(dst1, src1, sizeof(dst1));
	printf("Test 1: %s, Length: %zu\n", dst1, result1);

	char dst2[20] = "Hello, ";
	char src2[] = "World!";
	size_t result2 = fn(dst2, src2, 10);
	printf("Test 2: %s, Length: %zu\n", dst2, result2);

	char dst3[20] = "Hello, ";
	char src3[] = "World!";
	size_t result3 = fn(dst3, src3, 0);
	printf("Test 3: %s, Length: %zu\n", dst3, result3);

	char dst4[20] = "";
	char src4[] = "World!";
	size_t result4 = fn(dst4, src4, sizeof(dst4));
	printf("Test 4: %s, Length: %zu\n", dst4, result4);

	char dst5[20] = "Hello";
	char src5[] = "World!";
	size_t result5 = fn(dst5, src5, sizeof(dst5));
	printf("Test 5: %s, Length: %zu\n", dst5, result5);
}

int	main(void) {
	printf("REAL   \n");
	test_ft_strlcat(strlcat);
	printf("MINE   \n");
	test_ft_strlcat(ft_strlcat);
	return (0);
}
*/

/*
The	strlcpy(void) and strlcat() functions return the total length of the string
 they tried to create. For  strlcat() that means the initial length of dst
 plus the length of src.
  however, that if strlcat() traverses size characters without finding a NUL,
  the length of the string is considered to be size and the destination
  string will not be NUL-terminated
Breakdown of the Condition

   Understanding length_dst:
		length_dst is the length of the existing string in dst before any
			concatenation occurs. This is calculated using ft_strlen(dst).

   Understanding size:
		size is the total size of the buffer allocated for dst. This includes
			space for the existing characters in dst and any additional
			 characters
			from src,
			plus one extra byte for the null terminator ('\0').

   Condition Check:
		The condition if (size <= length_dst) checks whether the size of the
		buffer
		is less than or equal to the length of the existing string in dst.
		If this condition is true,
			it means that there is no space in the dst buffer to add any
				characters from src without exceeding the allocated size.

	*/
