/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:36:35 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/31 13:36:38 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

/*

int	main(void) {

	char test_char = 'A';

	if (ft_isprint(test_char)) {

		printf("'%c' is a printable character.\n", test_char);

	} else {

		printf("'%c' is not a printable character.\n", test_char);

	}


	return (0);

}
*/
