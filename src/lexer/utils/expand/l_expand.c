#include "../../../../includes/minishell.h"
#include "../../../../includes/lexer.h"
#include "../../../../includes/token.h"
#include "../../../../includes/execute.h"

char	**l_expand(char *str, t_env *env, int num)
{
	t_env	*head;
	char	**split;
	char	**returned;
	int		i = 0;

	split = NULL;
	returned = (char **)ft_calloc(3, sizeof(char *));
	head = env;
	split = ft_split(str, ' ');
	// printf("%s\n", str);
	while (head)
	{
		if (split)
		{
			i = 0;
			if (split)
			{
				if (num == 1)
				{
					returned[0] = ft_strdup(split[0]);
					returned[1] = NULL;
					returned[2] = NULL;
					// printf("IT: %s\n", returned[0]);
					return (returned);
				}
				if (num == 2)
				{
					if (!ft_strcmp(ft_substr(str, 0 , 1), head->key))
					{
						returned[0] = ft_strdup(head->value);
					// printf("SHE: %s\n", returned[0]);			// printf("HE: %s\n", returned[0]);
						returned[0] = ft_strjoin(returned[0], ft_substr(str, 1, ft_strlen(str)));
						returned[1] = ft_strdup(split[0]);
						returned[2] = NULL;
						// printf("HE: %s\n", returned[1]);
						return (returned);
					}
				}
				if (!ft_strcmp(split[i], head->key))
				{
					returned[0] = ft_strdup(head->value);
					returned[1] = ft_strdup(split[0]);
					returned[2] = NULL;
					// printf("SHE: %s\n", returned[0]);
					return (returned);
				}
			}
		}
		head = head->next;
	}
	return (NULL);
}

char	*l_handler_expand(char *value, char **expanded)
{
	char	**split;
	char	*first;
	char	*last;
	size_t 	len;
	size_t	first_len;
	int flag = 0;

	if (value[ft_strlen(value) - 1] == ' ')
		flag = 1;
	split = ft_split(value, ' ');
	// first = ft_strdup(expanded[1] + 1);
	if (!ft_strcmp(split[0], expanded[1]))
	{
		len = ft_strlen(expanded[1]);
		last = ft_substr(value, len + 1, ft_strlen(value));
		if (flag || split[1])
			last = ft_strjoin(" ", last);
		value = ft_strjoin(expanded[0], last);
	}
	else
	{
		first = ft_strdup(split[0]);
		len = ft_strlen(expanded[1]);
		first_len = ft_strlen(first);
		last = ft_substr(value, len + first_len, ft_strlen(value));
		value = ft_strjoin(first, expanded[0]);
		value = ft_strjoin(value, last);
	}
	return (value);
}

