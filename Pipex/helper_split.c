/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 07:53:18 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/12 20:49:43 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	word_count;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			word_count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (word_count);
}

static void	skip_separators(const char **s, char sep)
{
	while (**s == sep)
	{
		(*s)++;
	}
}

char	**ft_split_buff(char const *s, char sep, void *buff)
{
	const char		*start;
	t_split_state	curr;

	curr.buff_offset = 0;
	curr.word_count = count_words(s, sep);
	curr.arr = (char **)(buff + curr.buff_offset);
	curr.buff_offset += sizeof(char *) * (curr.word_count + 1);
	curr.word = 0;
	while (*s)
	{
		skip_separators(&s, sep);
		start = s;
		while (*s && *s != sep)
			s++;
		curr.word_len = s - start;
		if (curr.buff_offset + curr.word_len + 1 > SPLIT_BUFF_SIZE)
			return (NULL);
		curr.arr[curr.word] = (char *)buff + curr.buff_offset;
		ft_memcpy(curr.arr[curr.word], start, curr.word_len);
		curr.arr[curr.word++][curr.word_len] = '\0';
		curr.buff_offset += curr.word_len + 1;
		skip_separators(&s, sep);
	}
	curr.arr[curr.word] = NULL;
	return (curr.arr);
}

/*

char	**ft_split_buff(char const *s, char sep, void *buff)
{
	size_t		buff_offset;
	size_t		word_count;
	char		**arr;
	size_t		word;
	size_t		word_len;
	const char	*start;

	buff_offset = 0;
	word_count = count_words(s, sep);
	arr = (char **)(buff + buff_offset);
	buff_offset += sizeof(char *) * (word_count + 1);
	if (buff_offset > SPLIT_BUFF_SIZE)
	{
		return (NULL);
	}
	word = 0;
	while (*s == sep)
	{
		s++;
	}
	while (*s)
	{
		start = s;
		while (*s && *s != sep)
		{
			s++;
		}
		word_len = s - start;
		if (buff_offset + word_len + 1 > SPLIT_BUFF_SIZE)
		{
			return (NULL);
		}
		arr[word] = (char *)buff + buff_offset;
		ft_memcpy(arr[word], start, word_len);
		arr[word][word_len] = '\0';
		buff_offset += word_len + 1;
		word++;
		while (*s == sep)
		{
			s++;
		}
	}
	arr[word] = NULL;
	return (arr);
}

*/

/*
Proposed signature:

The function uses the buff to:
- allocate the pointer table
- cpy strs into the buffer and set the corresponding pointer in the table

The important thing is to keep track of where in the buffer to write next,
and make sure it doesn't write beyond SPLIT_BUFF_SIZE.

e.g.
size_t			buff_offset = 0;
arr = (char**)buff + buff_offset;
buff_offset += sizeof(char*) * count_words(s, sep) + 1;
arr[word++] = buff + buff_offset
// copy all bytes until sep
buff_offset += end - init + 1; // double check +1

Usage example:
char			split_buff[SPLIT_BUFF_SIZE];
char ** cmd_args = ft_split_buff(av[2], ' ', split_buff);
*/