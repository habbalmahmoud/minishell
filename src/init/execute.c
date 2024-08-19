#include "../../includes/ast.h"
#include "../../includes/minishell.h"
# include <sys/types.h>
# include <sys/wait.h>

void	e_execute_pipeline(t_ast_node *node, char **env)
{
	int	p_fd[2];
	int	pid;
	int	pid_2;

	if (node->left->type == AST_COMMAND 
		&& ft_strcmp(node->left->args[0], "()"))
	{
		pipe(p_fd);
		if ((pid = fork()) == -1)
			printf("Error\n");
		else if ((pid = fork()) == 1)
		{
			close(p_fd[0]);
			dup2(p_fd[1], 1);
			close(p_fd[1]);
			if (execve(node->left->args[0], node->left->args, env) == -1)
				printf("AHHHHHHH\n");
		}
		if ((pid_2 = fork()) == -1)
			printf("Error\n");
		else if ((pid_2 = fork()) == 1)
		{
			close(p_fd[1]);
			dup2(p_fd[0], 0);
			close(p_fd[0]);
			execve(node->right->args[0], node->right->args, env);
		}
		close(p_fd[1]);
		close(p_fd[0]);
	}

}

int	init_execute(t_syntax_tree *tree, char **env)
{
	if (tree->branch->type == AST_PIPE)
		e_execute_pipeline(tree->branch, env);
	return (0);
}
