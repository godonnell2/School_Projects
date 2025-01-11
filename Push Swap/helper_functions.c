/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:49 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/11 10:27:51 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_arr(int ac, char **av)
{
	int	i;

	if (!av)
		return ;
	(void)ac;
	i = 0;
	while (av[i])
		free(av[i++]);
	free(av);
}

void	parse_sign_and_whitespace(const char **str, int *sign)
{
	*sign = 1;
	while (**str == ' ' || **str == '\t' || **str == '\n' || **str == '\r'
		|| **str == '\v' || **str == '\f')
	{
		(*str)++;
	}
	while (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign *= -1;
		(*str)++;
	}
}
