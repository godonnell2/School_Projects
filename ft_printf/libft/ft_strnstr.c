/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:14:49 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/05 19:09:09 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[i])
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] && i <= len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j] && (i + j) < len)
		{
			j++;
		}
		if (j == ft_strlen(needle))
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

/*
   while( n[j] && h[i + j] == n[j] && (i +j) < len )
   NEED TO MAKE SURE I REMEMBER THE VALIDATIONS!!!
Basic substring found within the limit.
Substring not found within the limit.
Limit shorter than the full match.
Empty substring (should return the original string).
Empty main string.
Full match if n is large enough.
Limit of zero.
NEED TO ACCOUNT FOR LEN = 0 or we GET AN ERROR WHEN THERE IS A 
NULL STRING!!!! WE CAUSE A CRAASH BY TRYING TO DEREFERENCE NULL

*/
/*
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void	test_strnstr_functions(void)
{
	char	str1[];
	char	substr1[];
	size_t	len;
	char	*result_ft;
	char	*result_std;
	char	substr2[];
	char	substr3[];
	char	str2[];
	char	substr4[];
	char	str3[];
	char	substr5[];
	char	substr6[];
	char	substr7[];
	char	substr8[];
	char	str4[];
	char	substr9[];
	char	str5[];
	char	substr10[];

	str1[] = "Hello, World!";
	substr1[] = "World";
	substr2[] = "Mars";
	substr3[] = "";
	str2[] = "";
	substr4[] = "Hello";
	str3[] = "Hello";
	substr5[] = "Hello";
	substr6[] = "Hello, World!";
	substr7[] = "Hello";
	substr8[] = "!";
	str4[] = "abcabcabc";
	substr9[] = "abc";
	str5[] = "Hello, @World!";
	substr10[] = "@World";
	len = 12;
	result_ft = ft_strnstr(str1, substr1, len);
	result_std = strnstr(str1, substr1, len);
	// Print debug information
	if (result_ft != result_std)
	{
		printf("Assertion failed:\n");
		printf("ft_strnstr returned: %s\n", result_ft ? result_ft : "NULL");
		printf("strnstr returned: %s\n", result_std ? result_std : "NULL");
	}
	assert(result_ft == result_std);
	assert(ft_strnstr(str1, substr2, len) == strnstr(str1, substr2, len));
	len = 5;
	assert(ft_strnstr(str1, substr1, len) == strnstr(str1, substr1, len));
	len = 12;
	assert(ft_strnstr(str1, substr3, len) == strnstr(str1, substr3, len));
	assert(ft_strnstr(str2, substr4, len) == strnstr(str2, substr4, len));
	len = 10;
	assert(ft_strnstr(str3, substr5, len) == strnstr(str3, substr5, len));
	len = 0;
	assert(ft_strnstr(str1, substr1, len) == strnstr(str1, substr1, len));
	assert(ft_strnstr(str1, substr6, len) == strnstr(str1, substr6, len));
	len = 12;
	assert(ft_strnstr(str1, substr7, len) == strnstr(str1, substr7, len));
	assert(ft_strnstr(str1, substr8, len) == strnstr(str1, substr8, len));
	len = 9;
	assert(ft_strnstr(str4, substr9, len) == strnstr(str4, substr9, len));
	len = 15;
	assert(ft_strnstr(str5, substr10, len) == strnstr(str5, substr10, len));
	printf("All tests passed successfully.\n");
}

int	main(void)
{
	test_strnstr_functions();
	return (0);
}
*/