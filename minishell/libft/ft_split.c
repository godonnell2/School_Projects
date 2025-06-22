/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:51:28 by belinore          #+#    #+#             */
/*   Updated: 2024/11/20 20:33:32 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*alloc_str(char **str_array, size_t i, char const *s, char c);
static void		free_array(char **str_array, int index);
static size_t	word_count(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**str_array;
	size_t	words;
	size_t	i;
	size_t	j;

	words = word_count(s, c);
	str_array = ft_calloc(words + 1, sizeof(char *));
	if (str_array == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] == c)
			j++;
		str_array[i] = alloc_str(str_array, i, &s[j], c);
		if (str_array[i] == NULL)
		{
			free_array(str_array, i);
			return (NULL);
		}
		j += ft_strlen(str_array[i]);
		i++;
	}
	return (str_array);
}

static char	*alloc_str(char **str_array, size_t i, char const *s, char c)
{
	size_t	j;
	size_t	letters;

	j = 0;
	letters = 0;
	while (s[j] != c && s[j] != '\0')
	{
		letters++;
		j++;
	}
	str_array[i] = malloc(sizeof(char) * (letters + 1));
	if (str_array[i] == NULL)
		return (NULL);
	ft_strlcpy(str_array[i], &s[j - letters], letters + 1);
	return (str_array[i]);
}

static void	free_array(char **str_array, int index)
{
	while (index >= 0)
	{
		free(str_array[index]);
		index--;
	}
	free(str_array);
}

static size_t	word_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (s == NULL)
		return (0);
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}
/*
int	main(void)
{
    char	**split;
	int		i;

	split = ft_split("abc::def:ghi:::", ':');
//	split = ft_split("\0aa\0bbb", '\0');
	i = 0;
	while (split[i])
	{
		printf("%i : %s\n", i, split[i]);
		free(split[i]);
		i++;
	}
	printf("%i : %p\n", i, split[i]);
	free(split[i]);
	free(split);
}*/
