/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:16:17 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/31 11:32:43 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/builtins.h"
# include <sys/stat.h>
#include <errno.h>

int	e_traverse_tree(t_ast_node *node, t_exec_utils *util, t_env **env)
{
	if (!node)
		return (1);
	if (node->type == AST_COMMAND)
	{
		if (node && node->args && node->args[0])
			return (e_simple_command(node, util, env));
	}
	else if (node->type == AST_PIPE)
		e_pipeline(node, util, env);
	else if (node->type == AST_AND)
		e_operator_and(node, util, env);
	else if (node->type == AST_OR)
		e_operator_or(node, util, env);
	else
		printf("node type error");
	return (util->code);
}

void	e_operator_and(t_ast_node *node, t_exec_utils *util, t_env **env)
{
	if (!ft_strcmp(node->left->args[0], "()"))
		e_traverse_tree(node->left->tree_link->branch, util, env);
	else
		e_traverse_tree(node->left, util, env);
	if (util->code == EXIT_SUCCESS)
	{
		if (!ft_strcmp(node->right->args[0], "()"))
			e_traverse_tree(node->right->tree_link->branch, util, env);
		else
			e_traverse_tree(node->right, util, env);
	}
	else if (util->code == EXIT_FAILURE)
		return ;
}

void	e_operator_or(t_ast_node *node, t_exec_utils *util, t_env **env)
{
	if (!ft_strcmp(node->left->args[0], "()"))
		e_traverse_tree(node->left->tree_link->branch, util, env);
	else
		e_traverse_tree(node->left, util, env);
	if (util->code == EXIT_SUCCESS)
		return ;
	else if (util->code == EXIT_FAILURE)
	{
		if (!ft_strcmp(node->right->args[0], "()"))
			e_traverse_tree(node->right->tree_link->branch, util, env);
		else
			e_traverse_tree(node->right, util, env);
	}
}	

void e_pipeline(t_ast_node *node, t_exec_utils *util, t_env **env)
{
	int	fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int status;

	(void)env;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		util->code = EXIT_FAILURE;
		return ;
	}
	e_pipeline_parent(node, util, &pid1, fd);
	e_pipeline_child(node, util, &pid2, fd);
		
	close(fd[0]);
	close(fd[1]);
	e_pipeline_status(pid1, pid2, &status, util);
}

int	handle_exit(t_exec_utils *util, char **args)
{
	char	*delim;
	int	nbr;

	if (!args[1])
		exit(util->code);
	if (args[2])
	{
		ft_putendl_fd("too many arguments", 2);
		exit(1);
	}
	else if (args[1])
	{
		delim = ft_strchr(args[1], '+');
		if (delim)
		{
			nbr = ft_atoi(delim + 1);
			util->code += nbr;
			exit(util->code);
		}
		else if (!delim)
		{
			delim = ft_strchr(args[1], '-');
			if (delim)
			{
				nbr = ft_atoi(delim + 1);
				util->code = 256 - nbr;
				exit(util->code);
			}
		}
		int i = 0;
		while (args[1][i])
		{
			if (ft_isdigit(args[1][i]))
				i++;
			else
			{
				ft_putendl_fd("numeric argument required", 2);
				exit (2);
			}
		}
		nbr = ft_atoi(args[1]);
		if (nbr > 256)
			nbr -= 256;
		exit(nbr);
	}
	return (1);
}
int count_nodes(t_env *head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Function to copy linked list to array of strings
char **copy_list_to_array(t_env *head) {
    int length = count_nodes(head);
    char **array = malloc((length + 1) * sizeof(char *)); // +1 for NULL terminator
    if (!array) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (head) {
        // Calculate the length needed for the new string
        size_t key_len = strlen(head->key);
        size_t value_len = strlen(head->value);
        size_t str_len = key_len + value_len + 2; // +2 for '=' and '\0'

        // Allocate memory for the formatted string
        array[i] = malloc(str_len * sizeof(char));
        if (!array[i]) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // Format and copy the string into the array
        snprintf(array[i], str_len, "%s=%s", head->key, head->value);

        // Move to the next element
        head = head->next;
        i++;
    }

    // NULL-terminate the array
    array[i] = NULL;

    return array;
}

int	e_simple_command(t_ast_node *node, t_exec_utils *util, t_env **env)
{
	char *path;
	pid_t pid;
	int status;
	struct stat statbuf;
	char **array;

    if (!ft_strcmp(node->args[0], "env"))
    {
        exec_env(env, node->args);
        return (0);
    }
    if (!ft_strcmp(node->args[0], "unset"))
    {
        exec_unset(env, node->args);
	util->code = 0;
        return (0);
    }
    if (!ft_strcmp(node->args[0], "export"))
    {
        exec_export(env, util, node->args);
        return(0);
    }
    if (!ft_strcmp(node->args[0], "exit"))
    {
	if (handle_exit(util, node->args))
		return (0);
    }
    if (!ft_strcmp(node->args[0], "cd"))
    {
	change_dir(util, node->args);
	return (0);
    }
  
    if (!ft_strncmp(node->args[0], "/", 1) || !ft_strncmp(node->args[0], "./", 2))
        path = ft_strdup(node->args[0]);
    else
        path = get_path(node->args, env);
 
if (stat(path, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_putendl_fd(" Is a directory", 2);
			util->code = 126;
			util->exit_code = 126;
			free(path);
			return(126);
		}
	}
	int fd = access(path, X_OK);
	if (fd < 0 && errno == 13)
	{
		ft_putendl_fd(" invalid permissions", 2);
		util->code = 126;
		util->exit_code = 126;
		free(path);
		return(126);
	}
    pid = fork();
    if (pid == 0)
    {
		e_redirection(node, util);
		if (path)
		{
			array = copy_list_to_array((*env));
			execve(path, node->args, array);
		}	
		ft_putstr_fd(node->args[0], 2);
		ft_putendl_fd(":command not found", 2);
		util->code = 127;
		exit(127);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            util->code = WEXITSTATUS(status);
            util->exit_code = WEXITSTATUS(status);// Specific exit code from execve
        }
        else
        {
	    util->code = EXIT_FAILURE;
            util->exit_code = EXIT_FAILURE;
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    free(path);
    return (util->code);
}

void	e_redirection(t_ast_node *node, t_exec_utils *util)
{
	int	fd_in;
	int	fd_out;
	int	pipefd[2];

	(void)util;
	if (node->in)
	{
		if (node->exit)
			exit(node->exit);
		if (node->here_doc)
		{
			pipe(pipefd);
			handle_doc(node->in, pipefd);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		else
		{
			fd_in = open(node->in, O_RDONLY);
			if (fd_in < 0)
			{
				perror("open input");
				exit(EXIT_FAILURE);
			}
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
	}
	if (node->out)
	{
		if (node->exit)
			exit(node->exit);
		if (node->append)
		{
			fd_out = open(node->out, O_WRONLY | O_APPEND | O_CREAT , 0644);
		}
		else
			fd_out = open(node->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			ft_putendl_fd(" permission denied", 2);
			util->code = 1;
			exit(EXIT_FAILURE);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}
