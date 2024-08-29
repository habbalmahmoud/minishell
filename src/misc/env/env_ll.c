# include "../../../includes/minishell.h"

void	copy_env(t_env	**env_ll, char **env)
{
	int	i;
	char	*key;
	char	*value;

	i = 0;
	while (env[i])
	{
		split_env(env[i], &key, &value);
		env_lstadd_back(env_ll, key, value);
		free(key);
		free(value);
		i++;
	}
	env_lstadd_back(env_ll, "?", "0");
	(*env_ll)->og = env;
}

void	split_env(char *str, char **key, char **value)
{
	char	*temp;
	char	*delim;

	temp = ft_strdup(str);
	delim = ft_strchr(temp, '=');
	if (delim != NULL)
	{
		*delim = '\0';
		*key = ft_strdup(temp);
		*value = ft_strdup(delim + 1);
	}
	else
	{
		*key = ft_strdup(temp);
		*value = NULL;
	}
	free(temp);
}

void	print_env(t_env *head)
{
	t_env *current;

	current = head;
	while (current != NULL)
	{
		if (ft_isascii(current->key[1]))
		{
			ft_putstr_fd(current->key, 1);
		}
			ft_putchar_fd('=', 1);
		if (ft_isascii(current->value[1]))
			ft_putendl_fd(current->value, 1);
		current = current->next;
	}
}
