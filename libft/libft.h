/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:41:19 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/29 12:41:22 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h> //this is for alnum etc.
# include <stddef.h>
# include <stdio.h>  // this is for printf
# include <string.h> //this is for memset etc..

int		ft_isalnum(int i);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_toupper(int c);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
int		ft_atoi(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
void	*ft_memmove(void *dst, const void *src, size_t len);

#endif // LIBFT_H

/* need to include stddef here to include size_t  Prevent Multiple Definitions:
 If a header file is included multiple times in different source files or even
  within the same source file,
	without include guards,
	the compiler would see the same declarations and definitions multiple times,
	leading to errors like "redefinition of type" or "multiple definitions of
	functions."*/
