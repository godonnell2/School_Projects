/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:53:53 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/04 11:53:55 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

/*
for the close function
0644 is the permissions chmod etc...
$ IS NEWLINE
cat -e
% is NO newline
*/

/*
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	char	*temp_filename;
	int		fd;
	char	*s;

	temp_filename = "test_output.txt";
	fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1 )
	{
		return (1);
	}
	s = "Grace is the best";
	ft_putendl_fd(s, fd);
	close(fd);
	return (0);
}
*/
