/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:03:00 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 19:03:03 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_dir(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL) 
	{
		perror("getcwd() error");
		exit(1);
	}
	return (cwd);
}
