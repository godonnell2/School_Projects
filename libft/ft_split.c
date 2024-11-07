/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:37:08 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/07 14:23:49 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char const *s, char c)
{
	unsigned int	in_word;
	unsigned int	count;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			count++;
			in_word = 1;
		}
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	word_len;
	unsigned int	i;
	char			**arr;

	arr = (char **)malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			arr[i++] = ft_substr(s, 0, word_len);
			s = word_len + s;
		}
	}
	arr[i] = NULL;
	return (arr);
}
/*
The if (*s) statement is used to determine if there's any valid character left 
to process after skipping delimiters.
char ** and size of char * (8bytes not one its an address) is diff to char 
*/
/*void	free_split(char **arr)
{
	for (int i = 0; arr[i] != NULL; i++)
		free(arr[i]);
	free(arr);
}

int	main(void)
{
	char const	*str1;
	char const	*str2;
	char const	*str3;
	char const	*str4;
	char const	*str5;
	char		**result1;
	char		**result2;
	char		**result3;
	char		**result4;
	char		**result5;

	str1 = "Hello, world! This is a test.";
	str2 = "   Multiple    spaces   ";
	str3 = "NoDelimitersHere";
	str4 = "";
	str5 = "   ";
	result1 = ft_split(str1, ' ');
	result2 = ft_split(str2, ' ');
	result3 = ft_split(str3, ' ');
	result4 = ft_split(str4, ' ');
	result5 = ft_split(str5, ' ');
	for (int i = 0; result1 && result1[i] != NULL; i++)
		printf("result1[%d]: '%s'\n", i, result1[i]);
	printf("\n");
	for (int i = 0; result2 && result2[i] != NULL; i++)
		printf("result2[%d]: '%s'\n", i, result2[i]);
	printf("\n");
	for (int i = 0; result3 && result3[i] != NULL; i++)
		printf("result3[%d]: '%s'\n", i, result3[i]);
	printf("\n");
	for (int i = 0; result4 && result4[i] != NULL; i++)
		printf("result4[%d]: '%s'\n", i, result4[i]);
	printf("\n");
	for (int i = 0; result5 && result5[i] != NULL; i++)
		printf("result5[%d]: '%s'\n", i, result5[i]);
	printf("\n");
	free_split(result1);
	free_split(result2);
	free_split(result3);
	free_split(result4);
	free_split(result5);
	return (0);
}
*/
/*
int	main(void) {

	const char *str = "  Hello, how are you?    ";

	char delimiter = ' ';

	int word_count = ft_countwords(str, delimiter);

	printf("Number of words: %d\n", word_count); // Should print 4

	return (0);

}
*/
/*
Encounter 'H': Not a space, !in_word is true 
→ Increment count to 1, set in_word to 1.
Encounter 'e', 'l', 'l', ',': 
All are not spaces, in_word remains 1.
Encounter ' ': Is a space → Set in_word to 0.
Encounter 'w': Not a space, !in_word is true \addindex
 Increment count to 2, set in_word to 1.
*/