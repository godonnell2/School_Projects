/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 07:53:18 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/11 19:02:07 by gro-donn         ###   ########.fr       */
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
	char	*word[1000];
	size_t	i;

	
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

/*
Proposed signature:
#define SPLIT_BUFF_SIZE 100*1024 //enough?
char **ft_split_buff(char const *s, char sep, void* buff);

The function uses the buff to:
- allocate the pointer table
- cpy strs into the buffer and set the corresponding pointer in the table

The important thing is to keep track of where in the buffer to write next,
and make sure it doesn't write beyond SPLIT_BUFF_SIZE.

e.g. 
size_t buff_offset = 0;
arr = (char**)buff + buff_offset;
buff_offset += sizeof(char*) * count_words(s, sep) + 1; // Same as in malloc
arr[word++] = buff + buff_offset
// copy all bytes until sep
buff_offset += end - init + 1; // double check +1

return arr; as before

Usage example:
char split_buff[SPLIT_BUFF_SIZE];
char ** cmd_args = ft_split_buff(av[2], ' ', split_buff);
*/

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

void free_split(char **str)
{
	int i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}