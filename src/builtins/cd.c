/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:02:50 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/02 14:29:16 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_dir(const char *path, char *home) 
{
	if (path == NULL || path[0] == '\0')
	{
		if (chdir(home) != 0)
			perror("cd");
		return ;
	}

	if (path[0] == '~')
		path = ft_strjoin(home, ft_substr(path, 1, ft_strlen(path)- 1));
	if (chdir(path) != 0)
		perror("cd");
}
