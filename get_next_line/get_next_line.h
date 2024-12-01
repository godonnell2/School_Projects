/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:09:24 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/01 17:29:33 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# if BUFFER_SIZE < 1
#  error BUFFER_SIZE has to be >0
# endif

#include <stdlib.h>

size_t	ft_strlen_chr(char *str, char c);
char	*str_join_consume(char *current_line, char *new_read,
			size_t *line_length);
char	*get_next_line(int fd);

#endif
