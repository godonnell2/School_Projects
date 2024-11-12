/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:55:17 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/12 12:32:22 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstring(char *s, int fd)
{
	int	length;
	int error_check; 
	
	error_check = 0;
	if (s == NULL)
	{
		s = "(null)";
	}
	length = ft_strlen(s);
	
	error_check = ft_putstr_fd(s, fd);
	if(error_check == -1)
	{
		return -1;
	}
	return length;

}

// int main(){
// printf("%s", (char *)NULL);
// return (0);
// }