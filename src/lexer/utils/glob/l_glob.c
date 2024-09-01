/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_glob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:07:23 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/08 12:11:51 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include "../../../../includes/lexer.h"
#include <dirent.h>

char	**l_glob(const char *pattern, int *hits)
{
	struct dirent	*entry;
	DIR	*dir;
	size_t	i;
	size_t	j;
	char	**matches;

	i = l_glob_count(pattern);
	matches = (char **)malloc(sizeof(char *) * i);
	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return (0);
	}
	j = 0;
	while ((entry = readdir(dir)))
	{
		if (l_glob_match(pattern, entry->d_name))
		{
			matches[j] = ft_strdup(entry->d_name);
			j++;
		}
	}
	*hits = i;
	closedir(dir);
	return (matches);
}
