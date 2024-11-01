/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:34:20 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/01 10:34:22 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *end)
{
	unsigned int	i;

	while (*s1 && ft_strchr(end, *s1))
	{
		s1++;
	}
	i = ft_strlen(s1);
	while (i > 0 && ft_strrchr(end, s1[i]))
	{
		i--;
	}
	return (ft_substr(s1, 0, i + 1));
}

/*
i+ 1 because arrays are zero indexed
0 because youve already trimmed the start of the word
*/
/*
#include <stdio.h>

int main (void)
{
	char const	*s1;
	char const	*end;
	char		*trimmed;

   s1 = "xxgracexxxx";
   end = "x";
   trimmed = ft_strtrim(s1, end);
	printf("%s\n", trimmed);
	free(trimmed);
}
*/

/*
COULD ALSO DO IT THIS WAY!!
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		str = (char *)malloc(sizeof(char) * (j - i + 1));
		if (str)
			ft_strlcpy(str, &s1[i], j - i + 1);
	}
	return (str);
}

*/