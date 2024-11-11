/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:55:17 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/10 18:58:42 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstring(char *s, int fd)
{
	int	length;

	if (s == NULL)
	{
		s = "(null)";
	}
	length = ft_strlen(s);
	ft_putstr_fd(s, fd);
	return (length);
}

// int main(){
// printf("%s", (char *)NULL);
// return (0);
// }