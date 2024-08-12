#include "../../includes/ast.h"
#include "../../includes/token.h"

void	p_build_tree(t_token *token, t_ast_node *ast)
{
	if (token->type == TOKEN)
		// SEND TO BUILD COMMAND
		// BUILD 2D ARRAY OF CMD AND ARGS -> INIT NODE OUT OF THIS
	if (token->type == TYPE_PIPE)
		// SEND TO BUILD PIPE
		// TAKES IN LEFT NODE RETURNED FROM BUILD COMMAND AND RIGHT CMD RETURNED FROM BUILD CMD
	if (token->type == TYPE_LSHIFT)
		// SEND TO REDIRECT
		// SAME SAME
	
	// ETC ETC
}
