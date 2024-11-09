/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:08:08 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/06 10:18:12 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

/*
o fix this issue, you should modify the declaration of ft_strlen to
accept a const char * instead of char *. This change allows ft_strlen to
accept string literals]
 and other constant strings without warnings.
str += 1; CAN DO 
	
	str[2] = 3; CANT DO 
  const char* j = "joel";
		ft_strlen(j); //  adds 1 to j
		everything happens to a copy
		inside the fn would be oel outside would be joel
		j += 1;
	printf("%s\n", j);
*/