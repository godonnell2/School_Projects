/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:51 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/08 18:35:50 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_listhead;
	t_list	*tmp;
	void	*new_content;

	new_listhead = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		new_content = f(lst->content);
		tmp = ft_lstnew(new_content);
		if (tmp == NULL)
		{
			if (new_content != NULL)
				del(new_content);
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
	int	*new_content;

    new_content = malloc(sizeof(int));
    if(!new_content)
    return (NULL);
    *new_content = (*(int*)content) * 2;
    return (new_content);
}

void * ft_mapatoi(void *content)
{
   
    int * new_content = malloc(sizeof(int));
    if(!new_content)
    return (NULL);
    *new_content = ft_atoi((char *)content);
    return (new_content);
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

int	main(void)
{
	t_list	*head_node;
	t_list	*node_one;
	t_list	*node_second;
	t_list	*node_third;
	t_list	*new_head;

    char* one = "1";
    char* two = "2";
    char* three = "3";
    
    head_node = NULL;
    node_one = ft_lstnew(one);
    node_second = ft_lstnew(two);
    node_third = ft_lstnew(three);
   
    ft_lstadd_front(&head_node, node_one);
    ft_lstadd_back(&head_node,  node_second);
    ft_lstadd_back(&head_node, node_third);
    new_head = ft_lstmap(head_node, ft_mapatoi ,del);
    printf("Original list: \n");
    ft_lstiter(head_node, ft_print);
    
    printf("Mapped list: \n");
    ft_lstiter(new_head, ft_printint);
   
}
*/
/*
int	main(void)
{
	int		one;
	int		two;
	int		three;
	t_list	*head_node;
	t_list	*node_one;
	t_list	*node_second;
	t_list	*node_third;
	t_list	*new_head;

    one = 1;
    two = 2;
    three = 3;
    
    head_node = NULL;
    node_one = ft_lstnew(&one);
    node_second = ft_lstnew(&two);
    node_third = ft_lstnew(&three);
   
    ft_lstadd_front(&head_node, node_one);
    ft_lstadd_back(&head_node,  node_second);
    ft_lstadd_back(&head_node, node_third);
    new_head = ft_lstmap(head_node, ft_double ,del);
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