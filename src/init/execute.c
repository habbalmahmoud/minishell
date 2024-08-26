#include "../../includes/execute.h"

int	init_execute(t_syntax_tree *tree, t_env *env, t_exec_utils **util)
{
	(*util)->env = env;
	if (!tree)
		return (0);
	if (!tree->branch)
		return (0);
	if (!tree->branch->args)
		return (0);
	if (!ft_strcmp(tree->branch->args[0], "()"))
		e_traverse_tree(tree->branch->tree_link->branch, (*util));
	else
		e_traverse_tree(tree->branch, (*util));
	return (0);
}
