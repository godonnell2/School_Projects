/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_addfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:49:47 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/05 10:55:10 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}

Set the next of the new node to the current head
Update the head of the list to point to the new node
Setting the Next Pointer:

The next pointer of the new node is set to the
 current head of the list (*lst).

 updating the Head:
Finally, the head of the list is updated to point to the new node.
*/
#include "libft.h"

void ft_lstadd_front(t_list **lst, t_list *new)
{
    if(new == NULL)
        return ;
  new -> next = *lst;
  *lst = new;  
}

/*
int main()
{
    t_list *head;
    t_list *new = ft_lstnew("Grace is the best");
    
    ft_lstadd_front(&head ,new);
    printf("%s", (char *)head->content);
    return(0);
}
*/

/*
we initialize the head of the list
we make our new node to attach 
we set the address of head(as its a pointer ) to the new node

Printing the Content: In your main function, you are printing the content of 
the new node instead of the head of the list. After calling ft_lstadd_front,
 the new node is now the head of the list, so you should print head->content
  instead.  printf("%s", (char *)new->content);

  plus you need to cast it cos its currently  a voidstar
   printf("%s", head->content);FAIL

   if you initialize the head pointer to NULL, 
   which indicates that the list is currently empty.

BEFORE
head -> NULL (ie empty list)
AFTER
new_node -> "Grace is the best" -> NULL
head -> new_node
*/

/*
int main() {
    t_list *head = NULL; 
    t_list *new_node = ft_lstnew("Grace is the best"); 
    
    if (new_node == NULL) {

        return 1; 
    }

    ft_lstadd_front(&head, new_node); 

        if (head != NULL) {
        printf("%s\n", (char *)head->content); 
    }

    free(head);
    return 0;
}
*/