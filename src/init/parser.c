#include "../../includes/ast.h"
#include "../../includes/token.h"

void	init_parser(t_lexer **lex)
{
	t_ast_node	*node;
	t_lexer		*head;

	head = (*lex);
	(void)head;
	node = p_build_tree((*lex)->token_list);
	printf("%s\n", node->args[0]);
}
