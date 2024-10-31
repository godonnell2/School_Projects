/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:42:39 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/31 13:42:42 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (c + 32);
	}
	return (c);
}

/*

int	main(void) {

	char test_char1 = 'A';

	char test_char2 = 'Z';

	char test_char3 = 'a';

	char test_char4 = '1';



	printf("ft_tolower('%c') = '%c'\n", test_char1, ft_tolower(test_char1));
		// Should print 'a'

	printf("ft_tolower('%c') = '%c'\n", test_char2, ft_tolower(test_char2));
		// Should print 'z'

	printf("ft_tolower('%c') = '%c'\n", test_char3, ft_tolower(test_char3));
		// Should print 'a'

	printf("ft_tolower('%c') = '%c'\n", test_char4, ft_tolower(test_char4));
		// Should print '1'


	return (0);

}
*/
