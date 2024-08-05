/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:56 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/03 22:05:40 by nkanaan          ###   ########.fr       */
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

static size_t	ft_glob_init(const char *pattern)
{
	struct dirent	*entry;
	DIR	*dir;
	int	count;

	count = 0;
	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return (0);
	}
	while ((entry = readdir(dir)))
	{
		if (match(pattern, entry->d_name))
			count++;
	}
	closedir(dir);
	return (count);

}

char	**ft_glob(const char *pattern, int *hits)
{
	struct dirent	*entry;
	DIR	*dir;
	size_t	i;
	size_t	j;
	char	**matches;

	i = ft_glob_init(pattern);
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
		if (match(pattern, entry->d_name))
		{
			matches[j] = ft_strdup(entry->d_name);
			j++;
		}
	}
	*hits = i;
	closedir(dir);
	return (matches);
}
