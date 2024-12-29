/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 07:53:18 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/29 10:15:54 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char const *s, char c)
{
	size_t	i;
	size_t	nbr_words;

	nbr_words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			nbr_words++;
		while (s[i] != c && s[i])
			i++;
	}
	return (nbr_words);
}

static char	*copy_word(const char *s, int start, int end, int len)
{
	char	*word;
	size_t	i;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	init;
	size_t	end;
	size_t	word;

	arr = (char **)malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	if (!(arr) || !(s))
		return (NULL);
	init = 0;
	word = 0;
	while (s[init])
	{
		if (s[init] != c && s[init] != '\0')
		{
			end = init;
			while (s[end] && s[end] != c)
				end++;
			arr[word++] = copy_word(s, init, end, (end - init));
			init = end;
		}
		else
			init++;
	}
	arr[word] = NULL;
	return (arr);
}
