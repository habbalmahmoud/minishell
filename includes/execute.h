#ifndef EXECUTE_H
# define EXECUTE_H
# include "./minishell.h"
# include "./ast.h"


int	init_execute(t_syntax_tree *tree, char **env);

#endif
