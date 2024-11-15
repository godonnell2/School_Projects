/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:26:10 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/15 16:26:33 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

#endif
