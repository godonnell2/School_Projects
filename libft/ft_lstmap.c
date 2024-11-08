/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:51 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/08 10:29:35 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_listhead;
	t_list	*tmp;

	new_listhead = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp == NULL)
		{
			ft_lstclear(&new_listhead, del);
			return (NULL);
		}
		if (new_listhead == NULL)
			new_listhead = tmp;
		else
			ft_lstadd_back(&new_listhead, tmp);
		lst = lst->next;
	}
	return (new_listhead);
}

/*
void * ft_double(void *content)
{
    int *new_content = malloc(sizeof(int));
    if(!new_content)
    return NULL;
    *new_content = (*(int*)content) * 2;
    return new_content;
}

void * ft_mapatoi(void *content)
{   
    int * new_content = malloc(sizeof(int));
    if(!new_content)
    return NULL;
    *new_content = ft_atoi((char *)content);
    return new_content;

}

void	del(void *c)
{
	free(c);
}

void	ft_printint(void *content) 
{
    printf("%d\n", *(int *)content);
}


void	ft_print(void *content) 
{
    printf("string=%s\n", (char *)content);
}

int main()
{
    char* one = "1";
    char* two = "2";
    char* three = "3";
    
    t_list *head_node = NULL;
    t_list *node_one = ft_lstnew(one);
    t_list *node_second = ft_lstnew(two);
    t_list *node_third = ft_lstnew(three);

   
    ft_lstadd_front(&head_node, node_one);
    ft_lstadd_back(&head_node,  node_second);
    ft_lstadd_back(&head_node, node_third);
    t_list *new_head = ft_lstmap(head_node, ft_mapatoi ,del);
    printf("Original list: \n");
    ft_lstiter(head_node, ft_print);

    
    printf("Mapped list: \n");
    ft_lstiter(new_head, ft_printint);
   
}
*/
/*
int main()
{
    int one = 1;
    int two = 2;
    int three = 3;
    
    t_list *head_node = NULL;
    t_list *node_one = ft_lstnew(&one);
    t_list *node_second = ft_lstnew(&two);
    t_list *node_third = ft_lstnew(&three);

   
    ft_lstadd_front(&head_node, node_one);
    ft_lstadd_back(&head_node,  node_second);
    ft_lstadd_back(&head_node, node_third);
    t_list *new_head = ft_lstmap(head_node, ft_double ,del);
    printf("Original list: \n");
    ft_lstiter(head_node, ft_print);

    
    printf("Mapped list: \n");
    ft_lstiter(new_head, ft_printint);
   
}
*/
/* 
 im replacing the NULL with node one 
  ft_lstadd_back(&head_node,  node_second);
  this gets an address just to be consistent with front!!??
check if lst or f or del is NULL 
loop over lst 
create a new element 
 if new elem is null,
 if a node creation fails you want to delete the whole list
  clear the new list 
 add the new element to the back of the list 
 finally, return the new list 
 when add need to pass address!!!
 */