#include "../includes/minishell.h"
#include "../includes/execute.h"

t_env	*ft_lstcpy(t_env **stack)
{
	t_env	*src;
	t_env	*dest;
	t_env	**temp;

	src = *stack;
	dest = NULL;
	temp = &dest;
	while (src)
	{
		*temp = (t_env *)malloc(sizeof(t_env));
		if (!*temp)
			return (NULL);
		(*temp)->key = src->key;
		(*temp)->value = src->value;
		(*temp)->next = NULL;
		temp = &((*temp)->next);
		src = src->next;
	}
	return (dest);
}

void	bubble_sort(t_env **stack)
{
	int		swapped;
	char	*temp_content;
	char	*temp_key;
	t_env	*current;
	t_env	*last;

	last = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *stack;
		while (current->next != last)
		{
			if (current->key[0] > current->next->key[0])
			{
				temp_content = current->value;
				temp_key = current->key;
				current->key = current->next->key;
				current->value = current->next->value;
				current->next->key = temp_key;
				current->next->value = temp_content;
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	}
}

char *get_key_1(const char *str) {
    char *temp = strdup(str);
    char *delim = strchr(temp, '=');
    char *key;

    if (delim != NULL) {
        *delim = '\0';
        key = strdup(temp); // Duplicate key
    } else {
        key = strdup(temp); // Duplicate whole string if no '='
    }
    free(temp);
    return key;
}

char *get_value_1(const char *str) {
    char *temp = strdup(str);
    char *delim = strchr(temp, '=');
    char *value;

    if (delim != NULL) {
        value = strdup(delim + 1); // Duplicate value part
    } else {
        value = NULL;
    }
    free(temp);
    return value;
}


int	valid_export(char **args)
{
	if (!ft_isalpha(args[1][0]))
	{
		ft_putendl_fd(" not a valid identfier", 2);
		return (1);
	}
	if (ft_strchr(args[1], '-') || ft_strchr(args[1], '+'))
	{
		ft_putendl_fd(" not a valid identfier", 2);
		return (1);
	}
	if (args[1] && args[2] && args[3])
	{
		if (args[2][0] != '=')
		{
			ft_putendl_fd(" not a valid identfier", 2);
			return (1);
		}
	}
	return (0);
}

int	exec_export_2(t_env **env, char **args)
{
	t_env	*head;
	char	*key;
	char	*value;
	t_env	*new;
	int	flag;

	flag = 0;
	head = (*env);
	value = NULL;
	key = NULL;
	if (args)
	{
		if (valid_export(args))
			return (1);
		if (args[2] == NULL)
			key = ft_strdup(args[1]);
		else
		{
			key = ft_strdup(args[1]);
			value = ft_strdup(args[3]);
		}
		head = (*env);
		while (head)
		{
			if (!ft_strcmp(head->key, key))
				head->value = ft_strdup(value);
			else
				flag = 1;
			head = head->next;
		}
		if (flag)
		{
			new = env_lstnew(key, value);
			env_lstadd_back(env, new);
		}
	}
	return (0);
}

void	exec_export(t_env **env, t_exec_utils *util, char **args)
{
	t_env	*cpy;
	t_env	*head;

	cpy = ft_lstcpy(env);
	bubble_sort(&cpy);
	head = cpy;
	if (!args[1])
	{
		while (head)
		{
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
			head = head->next;
		}
		return ;
	}
	else
		util->code = exec_export_2(env, args);
}
