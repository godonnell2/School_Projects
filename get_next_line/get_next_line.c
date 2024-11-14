/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:59:05 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/14 14:59:10 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char *get_next_line(int fd)
{
    
}



#include <fcntl.h>

int main ()
{
	const char	*temp_filename = "test_output.txt";
	int			fd;
	char		*s;

	fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fd == -1) {
		perror("Failed to open file");
		return (1);
	}
	s = "GRACE";
	ft_putstr_fd(s, fd);
	return (0);
}

/*
create if nonexistsent
truncate if it exists let me overwrite

check if -1 is kinda like check for null
*/
