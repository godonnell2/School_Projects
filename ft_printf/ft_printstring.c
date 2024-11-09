/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:55:17 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/09 18:01:16 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printstring(char *s, int fd)
{
	int	length;

	length = ft_strlen(s);
	ft_putstr_fd(s, fd);
	return (length);
}
