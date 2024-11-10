/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:57:02 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/10 18:00:43 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *, ...);
int		ft_printchar(char c, int fd);
int		ft_printstring(char *s, int fd);
size_t	ft_printlong(long nb, int fd);
size_t	ft_printhex(int big, long nbr, int fd);
//int		ft_printpointer(unsigned long value, int asc);

#endif //FT_PRINTF_H
