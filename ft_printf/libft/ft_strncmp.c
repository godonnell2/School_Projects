/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:08:21 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/06 12:52:33 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s1 == *s2 && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/* 
Handling of Non-Printable Characters: When dealing with non-printable characters 
(like \200), you should ensure that your comparisons handle these correctly. 
The comparison you have (*(char*)s1 - *(char*)s2) is fine for ASCII values, 
but you need to ensure that you are correctly interpreting the characters
 when they are outside the standard ASCII range.
 Signed Characters: If char is signed, then characters with values greater
  than 127 will be interpreted as negative values. For example, if you 
  compare a character with a value of \200 (which is 128 in decimal), it could
   be treated as -128 if char is signed.
   Undefined Behavior:

While the operation itself (*s1 - *s2) will not cause undefined behavior 
directly, it may lead to incorrect comparisons, especially if you are 
working with extended ASCII characters. This can manifest in unexpected 
results when comparing strings that contain such characters.


 */
