/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:37:32 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/06 15:03:30 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	cap_length;

	cap_length = len;
	if (ft_strlen(s) < start)
		cap_length = 0;
	if (ft_strlen(s + start) < len)
		cap_length = ft_strlen(s + start);
	result = (char *)malloc(cap_length * sizeof(char) + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s + start, cap_length + 1);
	return (result);
}

/*
#include <stdio.h>

int main ()
{
	const char	s[];
	int			start;
	size_t		len;

	s[] = "tests";
	start = 3;
	len = 5;
	char * result = ft_substr(s, start, len);
	printf("%s",result);
}
*/

/*
malloc means not and NULL
need to remember strlcpy oh wait no i dont can copy manually in exam
so long as null terminate
if length of s is greater than start than cant run fn so	len = 0
Example 2
String: s = "Hello"
Start Index: start = 6
Explanation:

ft_strlen(s) returns 5.
Since 5 < 6 is true, the condition executes, and len is set to 0.
Suppose you have:

    s = "Hello, World!"
    start = 7 (which points to the character 'W')
    len = 10

The length of the substring starting from index 7 is 6 (the substring is
 "World!"). Since 6 is less than 10, the condition will be true, and len 
 will be updated to 6. This means that the function will safely extract 
 "World!" instead of trying to extract more characters than are available.

*/
