#include "../../../../includes/ast.h"
#include "../../../../includes/token.h"


t_ast_node	*p_build_simple_command(char *cmd, char *in, char *out, int id)
{
	t_ast_node *node;

	node = NULL;
	node = ft_calloc(1, sizeof(t_ast_node));
	if(cmd)
	{
		node->args = ft_split(cmd, ' ');
		node->type = AST_COMMAND;
		node->in = in;
		node->out = out;
		node->right = NULL;
		node->left = NULL;
		node->id = id;
		
	}
	return (node);
}

t_ast_node	*p_build_pipe(t_ast_node *left, t_ast_node *right, int id)
{
	t_ast_node *node;

	node = ft_calloc(1, sizeof(t_ast_node));
	node->left = left;
	node->right = right;
	node->type = AST_PIPE;
	node->args = ft_split("|", ' ');
	node->id = id;
	return (node);
}

