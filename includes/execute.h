#ifndef EXECUTE_H
# define EXECUTE_H
# include "./minishell.h"
# include "./ast.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_exec_utils
{
	int	code;
	int	*exit_codes;
	int	code_count;
	char	**env;
}   t_exec_utils;

int	init_execute(t_syntax_tree *tree, char **env);
char	*get_path(char **s_cmd, char **env);



void	e_traverse_tree(t_ast_node *node, t_exec_utils *util);

void	e_pipeline(t_ast_node *node, t_exec_utils *util);
void	e_pipeline_parent(t_ast_node *node, t_exec_utils *util, int *pid, int fd[2]);
void	e_pipeline_child(t_ast_node *node, t_exec_utils *util, int *pid, int fd[2]);
void	e_pipeline_status(int pid1, int pid2, int *status, t_exec_utils *util);

void	e_redirection(t_ast_node *node, t_exec_utils *util);

void	e_simple_command(t_ast_node *node, t_exec_utils *util);

void	e_operator_and(t_ast_node *node, t_exec_utils *util);
void	e_operator_or(t_ast_node *node, t_exec_utils *util);
#endif
