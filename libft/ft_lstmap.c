/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:51 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/07 16:30:59 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *new_list;
    t_list *tmp; 
    tmp = new_list; 
    
    if(!lst || !f || !del)
        return  NULL;
    
    new_list = ft_lstnew(lst->content); 
    
    while(ptr !=NULL)
    {
        

    }
    return ptr;
}
