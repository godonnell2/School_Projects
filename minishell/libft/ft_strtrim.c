/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:50:45 by belinore          #+#    #+#             */
/*   Updated: 2024/11/21 15:31:55 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*string;
	int		start;
	int		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	while (ft_strchr(set, s1[end - 1]) && end > start)
		end--;
	string = ft_substr(s1, start, end - start);
	return (string);
}
/*
int	main(void)
{
 	char *s1 = "abcabcabhelabcloabbc";
 	char *trimmed = "helabclo";
 	char *result = ft_strtrim(s1, "abc");
 
 	if (!strcmp(result, trimmed))
 		printf("OK");
 	else
		printf("NOK");
}*/
