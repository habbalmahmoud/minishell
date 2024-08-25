/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:52 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/30 16:29:53 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	exec_env(t_env **env, char **args)
{
	t_env	*head;

	head = (*env);
	if (!args[1])
		print_env(head);
	if (args[1])
	{
		char *delim;
		delim = ft_strchr(args[1], '$');
		while (head)
		{
			if (delim)
			{
				if (!ft_strcmp(delim + 1, head->key))
				{
					printf("%s\n", head->value);
					return ;
				}
			}
			head = head->next;
		}
		printf("env: %s: no such file or directory\n", args[1]);
	}
}
