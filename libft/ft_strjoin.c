/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:31:18 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/01 10:31:21 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_total;
	char	*arr;

	len_total = ft_strlen(s1) + ft_strlen(s2) + 1;
	arr = (char *)malloc(len_total * sizeof(char));
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, len_total);
	ft_strlcat(arr, s1, len_total);
	ft_strlcat(arr, s2, len_total);
	return (arr);
}

/*
removed validation because i think it-s meant to crash
*/

/*
int	main(void)
{
	char const	*s1;
	char const	*s2;
	char		*arr;

	s1 = NULL;
	s2 = "grace";
	arr = ft_strjoin(s1, s2);
	printf("%s", arr);
	free(arr);
}
*/