#include "../includes/builtins.h"

void	modify_oldpwd(t_env **env, char *oldpwd)
{
	t_env	*head;
	t_env	*new;

	head = (*env);
	while (head)
	{
		if (!ft_strcmp(head->key, "OLDPWD"))
		{
			head->value = ft_strdup(oldpwd);
			return ;
		}
		head = head->next;
	}
	new = env_lstnew("OLDPWD", oldpwd);
	env_lstadd_back(env, new);
}

char	*get_home_path(t_env **env)
{
	t_env	*temp;
	char	*home;

	temp = (*env);
	home = NULL;
	while (temp)
	{
		if(!ft_strcmp(temp->key, "HOME"))
		{
			home = ft_strdup(temp->value);
			break;
		}
		temp = temp->next;
	}
	return (home);
}

void	change_dir(t_exec_utils *util, char **args) 
{
	char	*home;
	char 	*path;
	char	*oldpwd;

	home = get_home_path(&util->env);
	oldpwd = getcwd(NULL, 0);
	modify_oldpwd(&util->env, oldpwd);
	if (args[2])
	{
		ft_putendl_fd(" too many arguments", 2);
		util->code = 1;
		return ;
	}
	if (args[1] == NULL)
	{
		if (chdir(home) != 0)
		{
			util->code = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;	
		}
		util->code = 0;
		return ;
	}
	path = ft_strdup(args[1]);
	if (path)
	{
		if (path[0] == '~')
			path = ft_strjoin(home, ft_substr(path, 1, ft_strlen(path)- 1));
		if (chdir(path) != 0)
		{
			util->code = 1;	
			perror("cd");
			return ;
		}
		util->code = 0;
	}
}
