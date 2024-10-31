/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:01:52 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/31 11:01:55 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr;
	char	*str;
	int		len;

	str = (char *)s;
	chr = (char)c;
	len = ft_strlen(str);
	if (chr == '\0')
		return (str + len);
	while (*str)
	{
		if (chr == *str)
		{
			return (str);
		}
		str++;
	}
	return (NULL);
}

/*
handle \0;
return str or str + len
*/
/*
#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c);

void	test_strchr(const char *str, int ch) {
	char *result_lib = strchr(str, ch);
	char *result_custom = ft_strchr(str, ch);


	if (result_lib == result_custom) {
		printf("Test passed: strchr(\"%s\", '%c') = \"%s\"\n", str, ch,
			result_lib ? result_lib : "NULL");
	} else {
		printf("Test failed: strchr(\"%s\", '%c')\n", str, ch);
		printf("  Standard: \"%s\"\n", result_lib ? result_lib : "NULL");
		printf("  Custom:   \"%s\"\n", result_custom ? result_custom : "NULL");
	}
}

int	main(void) {

	printf("Testing ft_strchr against strchr:\n");

	test_strchr("hello, world!", 'o');
	test_strchr("hello, world!", 'z');
	test_strchr("", 'a');
	test_strchr("banana", 'a');


	test_strchr("abcdef", 'a');
	test_strchr("abcdef", 'f');
	test_strchr("abcdef", 'c');


	test_strchr("hello, world!", ' ');
	test_strchr("hello, world!", ',');


	test_strchr("hello\0world", '\0');
	test_strchr("hello\0world", 'h');

	return (0);
}

*/
