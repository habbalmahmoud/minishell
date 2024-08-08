/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:25:33 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/08 13:38:00 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/list.h"


t_list	*ft_lstmap(t_list *lst, void *(*f)(int))
{
	t_list	*new;
	t_list	*res;

	res = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->id));
		if (!new)
			ft_lstdelone(new);
		else
			ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}
