#include "../../includes/ast.h"
#include "../../includes/token.h"

void	p_build_tree(t_token *token, t_tree *ast)
{
	(void)ast;
	if (token->type == TYPE_PIPE)
		printf("THIS IS A PIPE\n");
}
