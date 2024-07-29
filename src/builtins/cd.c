/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:02:50 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 19:02:53 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_dir(const char *path) 
{
	if (path == NULL || path[0] == '\0')
	{
		printf("cd: missing argument\n");
		return ;
	}

	if (chdir(path) != 0)
		perror("cd");
}
