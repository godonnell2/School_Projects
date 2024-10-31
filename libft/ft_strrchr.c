/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:03:11 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/31 11:03:14 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	char	*str;

	chr = (char)c;
	str = (char *)s;
	if (chr == '\0')
		return (ft_strlen(str) + str);
	while (*str)
		str++;
	while (str >= s)
	{
		if (chr == *str)
			return (str);
		str--;
	}
	return (NULL);
}

/*
NEED REMEMBER YOU HAVE TO GO TO START OF S
 #include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *s, int c);

void	test_strrchr(const char *str, int ch) {
	char *result_lib = strrchr(str, ch);
	char *result_custom = ft_strrchr(str, ch);


	if (result_lib == result_custom) {
		printf("Test passed: strrchr(\"%s\", '%c') = \"%s\"\n", str, ch,
			result_lib ? result_lib : "NULL");
	} else {
		printf("Test failed: strrchr(\"%s\", '%c')\n", str, ch);
		printf("  Standard: \"%s\"\n", result_lib ? result_lib : "NULL");
		printf("  Custom:   \"%s\"\n", result_custom ? result_custom : "NULL");
	}
}

int	main(void) {

	printf("Testing ft_strrchr against strrchr:\n");


	test_strrchr("hello, world!", 'o');
	test_strrchr("hello, world!", 'z');
	test_strrchr("", 'a');
	test_strrchr("banana", 'a');


	test_strrchr("abcdef", 'a');
	test_strrchr("abcdef", 'f');
	test_strrchr("abcdef", 'c');


	test_strrchr("hello, world! hello again!", 'h');
	test_strrchr("hello, world! hello again!", 'e');


	test_strrchr("hello, world!", ' ');
	test_strrchr("hello, world!", ',');
	test_strrchr("hello\nworld", '\n');


	test_strrchr("hello\0world", '\0');
	test_strrchr("hello\0world", 'h');

	return (0);
}

*/
