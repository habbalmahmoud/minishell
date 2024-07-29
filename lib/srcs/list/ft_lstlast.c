/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:33:48 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:18 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
// #include <stdio.h>
// int main() {
//     // Create a sample linked list: 1 -> 2 -> 3 -> NULL
//     t_list *head = (t_list *)malloc(sizeof(t_list));
//     t_list *second = (t_list *)malloc(sizeof(t_list));
//     t_list *third = (t_list *)malloc(sizeof(t_list));

//     head->content = 1;
//     head->next = second;

//     second->content = 2;
//     second->next = third;

//     third->content = 3;
//     third->next = NULL;

//     // Call ft_lstlast to get the last element
//     t_list *last = ft_lstlast(head);

//     // Print the data of the last element
//     if (last != NULL) {
//         printf("Last element data: %d\n", last->content);
//     } else {
//         printf("List is empty.\n");
//     }

//     // Clean up: free allocated memory
//     free(head);
//     free(second);
//     free(third);

//     return 0;
// }
