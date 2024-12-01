/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:09:24 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/01 19:30:53 by gro-donn         ###   ########.fr       */
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

size_t	ft_strlen_chr(char *str, char c);
char	*str_join(const char *current_line, const char *new_read,
			size_t current_len, size_t new_read_len);
char	*str_join_consume(char *current_line, char *new_read,
			size_t *line_length);
void	consume_new_read(char *new_read, size_t new_read_len);
char	*get_next_line(int fd);

#endif
