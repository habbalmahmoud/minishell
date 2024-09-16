/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_glob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:07:23 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/08 15:45:57 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include "../../../../includes/lexer.h"
#include <dirent.h>

char	**l_glob(const char *pattern, int *hits)
{
	struct dirent	*entry;
	DIR				*dir;
	size_t			i;
	size_t			j;
	char			**matches;

	i = l_glob_count(pattern);
	matches = (char **)malloc(sizeof(char *) * i);
	dir = opendir(".");
	j = 0;
	entry = readdir(dir);
	while ((entry))
	{
		if (l_glob_match(pattern, entry->d_name))
		{
			matches[j] = ft_strdup(entry->d_name);
			j++;
		}
		entry = readdir(dir);
	}
	*hits = i;
	closedir(dir);
	if (j < 1)
		return (free(matches), NULL);
	return (matches);
}
