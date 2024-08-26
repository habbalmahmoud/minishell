/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:36:11 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:18 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (lst == NULL)
		return ;
	while (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	end = ft_lstlast(*lst);
	end->next = new;
}

void	l_lstadd_back(t_lex_ll **lst, t_lex_ll *new)
{
	t_lex_ll	*end;

	if (lst == NULL)
		return ;
	while (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	end = l_lstlast(*lst);
	end->next = new;
}

void	env_lstadd_back(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*end;

	new = env_lstnew(key, value);
	if (env == NULL)
		return ;
	while (*env == NULL)
	{
		*env = new;
		return ;
	}
	end = env_lstlast(*env);
	end->next = new;
}

