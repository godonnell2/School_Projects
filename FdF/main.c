/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:26:05 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/29 23:26:38 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

int	error(char *error_message)
{
	ft_printf("%s\n", error_message);
	exit (1);
}
