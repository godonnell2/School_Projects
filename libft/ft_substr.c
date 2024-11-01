/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:37:32 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/01 14:37:35 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	result = (char *)malloc(len * sizeof(char) + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}

/*
int main ()
{
	const char	s[] = "tests";
	int			start;
	size_t		len;

	start = 3;
	len = 5;
	printf("%s",ft_substr(s, start, len));
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


*/
