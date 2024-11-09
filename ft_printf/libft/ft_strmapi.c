/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:08 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/04 11:54:10 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	length;
	char			*result;
	int				i;

	length = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * length + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
#include <stdio.h>
#include <stdlib.h>

char	ft_toupper_wrapper(unsigned int index, char c)
{
	(void) index;
	return (char)ft_toupper(c);
}

int main ()
{
	char const	*s;
	char		*result;

	s = "grace";
	result = ft_strmapi(s, ft_toupper_wrapper);
	printf("%s", result);
	free(result);
	return (0);
}
*/
