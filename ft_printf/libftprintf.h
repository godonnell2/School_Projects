/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:57:02 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/09 20:05:01 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *, ...);
int		ft_printchar(char c, int fd);
int		ft_printstring(char *s, int fd);
size_t	ft_printlong(long nb, int fd);
size_t	ft_printhex(long nbr, int fd);
int		ft_printpointer(unsigned long value, int asc);

#endif //LIBFTPRINTF_H
