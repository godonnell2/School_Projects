/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:06:44 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/28 16:27:27 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i >= '0'
			&& i <= '9'))
		return (1);
	return (0);
}
