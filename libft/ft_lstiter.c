/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:34 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/06 13:18:35 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;

	ptr = lst;
	while (ptr != NULL)
	{
		f(ptr->content);
		ptr = ptr->next;
	}
}
/*
void	ft_print(void *content) 
{
    printf("%s\n", (char *)content);
}

int	main(void)
{
	t_list	*lst;

    lst = ft_lstnew(ft_strdup("Grace"));
    lst->next = ft_lstnew(ft_strdup("is the "));
    lst->next->next = ft_lstnew(ft_strdup("best"));
    ft_lstiter(lst, ft_print);
    return (0);
}
*/