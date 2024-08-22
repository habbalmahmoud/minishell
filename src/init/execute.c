#include "../../includes/execute.h"

int	init_execute(t_syntax_tree *tree, char **env)
{
	t_exec_utils *util;

	util = ft_calloc(1, sizeof(t_exec_utils));
	util->env = env;
	e_traverse_tree(tree->branch, util);
	free(util);
	return (0);
}

