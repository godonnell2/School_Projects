/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:02:54 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/31 11:02:56 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	chr;
	unsigned char	*str;
	size_t			i;

	i = 0;
	chr = (unsigned char)c;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == chr)
		{
			return (str + i);
		}
		i++;
	}
	return (NULL);
}

/*
Needed size_t because you dont have the null byte so that
is how you set the limit of your loop otherwise impossible
*/

/*
#include <assert.h>
#include <stdio.h>
#include <string.h>


void	test_memchr_functions(void) {
	char test_string[] = "Hello, World!";
	char test_char = 'o';
	size_t length = strlen(test_string);


	assert(ft_memchr(test_string, test_char, length) == memchr(test_string,
			test_char, length));


	test_char = 'x';
	assert(ft_memchr(test_string, test_char, length) == memchr(test_string,
			test_char, length));


	test_char = 'H';
	assert(ft_memchr(test_string, test_char, length) == memchr(test_string,
			test_char, length));


	test_char = '!';
	assert(ft_memchr(test_string, test_char, length) == memchr(test_string,
			test_char, length));


	test_char = 'H';
	assert(ft_memchr(test_string, test_char, 0) == memchr(test_string,
			test_char, 0));

	test_char = 'o';
	assert(ft_memchr(test_string, test_char, 5) == memchr(test_string,
			test_char, 5));

	printf("All tests passed successfully.\n");
}

int	main(void) {
	test_memchr_functions();
	return (0);
}
*/
