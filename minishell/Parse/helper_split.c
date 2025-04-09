/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 07:53:18 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/17 15:52:37 by gro-donn         ###   ########.fr       */
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
