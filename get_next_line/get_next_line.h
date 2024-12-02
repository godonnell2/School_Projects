/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:09:24 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/02 11:20:57 by gro-donn         ###   ########.fr       */
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

# include <stdlib.h>

char	*get_next_line(int fd);
char	*strjoin_consumebuff(char *current_line, char *new_read,
			size_t *line_length);

#endif
