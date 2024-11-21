/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:26:10 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/21 10:16:14 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>




char    *get_next_line(int fd);
char    *ft_strdup(const char *s);
size_t    ft_strlen(const char *s);
char    *ft_substr(const char *s, unsigned int start, size_t len);
char    *ft_strjoin(const char *s1, const char *s2);
void    fill_str(const char *res, char *s1, char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strchr( char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
#endif
