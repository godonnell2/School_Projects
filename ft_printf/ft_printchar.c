/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:54:40 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/09 17:54:41 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printchar(char c, int fd)
{
	ft_putchar_fd(c, fd);
	return (1);
}

/*
return number is number of chars written 
*/