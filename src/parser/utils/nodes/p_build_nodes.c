#include "../../../../includes/ast.h"
#include "../../../../includes/token.h"


t_ast_node	*p_build_simple_command(t_ast_utils *util)
{
	t_ast_node *node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (util->args)
	{
		if (!ft_strncmp(util->args, "echo", 4) && util->echo_flag == 0)
		{
			node->args = malloc(3 * sizeof(char *));
			node->args[0] = ft_strdup("echo");
			node->args[1] = ft_substr(util->args, 5, ft_strlen(util->args));
			node->args[2] = NULL;
		}
		else
			node->args = ft_split(util->args, ' ');
		node->type = AST_COMMAND;
		node->in = util->files[1];
		node->out = util->files[0];
		node->exit = util->exit;
		node->append = util->append;
		node->here_doc = util->here_doc;
		node->right = NULL;
		node->left = NULL;
		if (util->sub)
			node->lexer = util->sub;
	}
	return (node);
}

t_ast_node	*p_build_separator(t_ast_node *left, t_ast_node *right, int type)
{
	t_ast_node	*node;
	char		*delim;

	node = ft_calloc(1, sizeof(t_ast_node));
	node->left = left;
	node->right = right;
	node->type = ASSIGN_TYPE(type);
	delim = ASSIGN(type);
	node->args = ft_split(delim, ' ');
	return (node);
}
