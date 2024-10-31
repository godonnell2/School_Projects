/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:02:35 by gro-donn          #+#    #+#             */
/*   Updated: 2024/10/31 11:02:37 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_mem;
	void	*ptr;

	if (count == 0 || size == 0)
	{
		return (malloc(0));
	}
	if (count > SIZE_MAX / size)
	{
		return (NULL);
	}
	total_mem = count * size;
	ptr = malloc(total_mem);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_mem);
	return (ptr);
}

/*
HAVE TO REMEMEMVER TO BZERO FOR CALLOC
NEED TO REMEMBER WHEN SET TO ZERO DUH!!!!
The line return (malloc(0)); allows the function to return a valid pointer that
 can be freed, even if it points to a zero-sized allocation. This is
 consistent with the behavior of calloc in standard C.
if you have a count and you have size easy to malloc
but must remember null
and need to return a ptr it s just a void ptr !!
For example, in C, the type size_t has a maximum value defined by SIZE_MAX
When you multiply count and size, you want to ensure that the result (total_mem
) does not exceed SIZE_MAX.
*/

/*
#include <stdio.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size);

int	main(void) {
	size_t count = 5; // Number of elements
	size_t size = sizeof(int); // Size of each element (int)

	// Allocate memory for an array of 5 integers
	int *array = (int *)ft_calloc(count, size);
	if (array == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return (1); // Exit with error code
	}
}
*/