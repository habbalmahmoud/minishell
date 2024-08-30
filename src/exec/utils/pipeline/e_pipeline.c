/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipeline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:16:24 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/26 11:45:02 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../../includes/execute.h"

void	e_pipeline_parent(t_ast_node *node, t_exec_utils *util, int *pid, int fd[2])
{
	(*pid) = fork();
	if ((*pid) == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (!ft_strcmp(node->left->args[0], "()"))
			e_traverse_tree(node->left->tree_link->branch, util, &util->env);
		else
			e_traverse_tree(node->left, util, &util->env);
		exit(EXIT_SUCCESS);
	}
	else if ((*pid) < 0)
	{
		perror("fork");
		util->code = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}

}

void	e_pipeline_child(t_ast_node *node, t_exec_utils *util, int *pid, int fd[2])
{
	(*pid) = fork();
	if ((*pid) == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (!ft_strcmp(node->right->args[0], "()"))
			e_traverse_tree(node->right->tree_link->branch, util, &util->env);
		else
			e_traverse_tree(node->right, util, &util->env);
		exit(EXIT_SUCCESS);
	}
	else if ((*pid) < 0)
	{
		perror("fork");
		util->code = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

void	e_pipeline_status(int pid1, int pid2, int *status, t_exec_utils *util)
{
	waitpid(pid1, status, 0);
	if (WIFEXITED((*status)))
		util->code = WEXITSTATUS((*status));
	else
		util->code = EXIT_FAILURE;
	waitpid(pid2, status, 0);
	if (WIFEXITED((*status)))
		util->code = WEXITSTATUS((*status));
	else
		util->code = EXIT_FAILURE;
}
