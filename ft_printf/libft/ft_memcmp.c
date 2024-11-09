/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:25:29 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/31 11:25:32 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

/*
if we dont find a difference we return 0
*/

/*
#include <assert.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n);

void	test_memcmp_functions(void) {

	char str1[] = "Hello, World!";
	char str2[] = "Hello, World!";
	size_t len = strlen(str1);
	assert(ft_memcmp(str1, str2, len) == memcmp(str1, str2, len));


	char str3[] = "Hello, World!";
	char str4[] = "Hello, Mars!";
	len = strlen(str3);
	assert(ft_memcmp(str3, str4, len) == memcmp(str3, str4, len));


	char str5[] = "";
	char str6[] = "";
	len = strlen(str5);
	assert(ft_memcmp(str5, str6, len) == memcmp(str5, str6, len));


	char str7[] = "Hello";
	char str8[] = "Hello, World!";
	len = strlen(str7);
	assert(ft_memcmp(str7, str8, len) == memcmp(str7, str8, len));


	char str9[] = "Aello, World!";
	char str10[] = "Hello, World!";
	len = strlen(str9);
	assert(ft_memcmp(str9, str10, len) == memcmp(str9, str10, len));

	printf("All tests passed successfully.\n");
}

int	main(void) {
	test_memcmp_functions();
	return (0);
}
*/
