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
				temp_content = current->key;
				current->key = current->next->key;
				current->next->key = temp_content;
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	}
}

int	split_env_h(char *str, char **key, char **value)
{
	char	*temp;
	char	*delim;
	int	i;

	temp = ft_strdup(str);
	delim = ft_strchr(temp, '=');
	i = 0;
	//printf("delim: %s\ntemp: %s\n", delim, temp);
	if (!temp[1])
		return (1);
	while (temp[i])
	{
		if (temp[i] == '-' && temp[i + 1] == '=')
			return (1);
		if (temp[i] == '-' && !delim)
			return (1);
		i++;
	}
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
	return (0);
}

int	exec_export_2(t_env **env, char *cmd)
{
	t_env	*head;
	int	flag = 0;
	char	*value;
	char	*key;

	if (cmd)
	{	
		if (split_env_h(cmd, &key, &value))
		{
			ft_putendl_fd(" not a valid identifier", 2);
			return (1);
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
			env_lstadd_back(env, key, value);
	}
	return (0);
}

void	exec_export(t_env **env, t_exec_utils *util, char **args)
{
	t_env	*cpy;

	cpy = ft_lstcpy(env);
	bubble_sort(&cpy);
	t_env	*head = cpy;
	if (!args[1])
	{
		while (head)
		{
			printf("declare -x %s=%s\n", head->key, head->value);
			head = head->next;
		}
		return ;
	}
	int	i = 1;
	while (args[i])
	{
		if (args[i])
			util->code = exec_export_2(env, args[i]);
		i++;
	}
}
