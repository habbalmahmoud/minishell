/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:56 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/01 15:42:57 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/lexer.h"
# include <dirent.h>

static int	match(const char *pattern, const char *string)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (!*pattern)
				return 1;
			while (*string)
			{
				if (match(pattern, string))
					return (1);
				string++;
			}
			return (0);
		}
		else if (*pattern == '?')
		{
			if (!*string)
				return (0);
			pattern++;
			string++;
		}
		else
		{
			if (*pattern != *string)
				return (0);
			pattern++;
			string++;
		}
	}
	return (*string == '\0');
}

char	**ft_glob(const char *pattern, int *hits)
{
	struct dirent *entry;
	DIR	*dir;
	int		count;
	char	**matches;

	matches = NULL;
	count = 0;
	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return (NULL);
	}
	while ((entry = readdir(dir)))
	{
		if (match(pattern, entry->d_name))
		{
			matches = realloc(matches, (count + 1) * sizeof(char *));
			if (matches == NULL)
			{
				perror("realloc");
				closedir(dir);
				return (NULL);
			}
			matches[count] = ft_calloc(1, ft_strlen(entry->d_name) + 1);
			if (!matches[count])
			{
				perror("malloc");
				closedir(dir);
				return (NULL);
			}
			ft_strcpy(matches[count], entry->d_name);
			count++;
		}
	}
	closedir(dir);
	*hits = count;
	return (matches);
}


