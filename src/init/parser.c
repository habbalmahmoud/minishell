# include "../../includes/ast.h"
# include "../../includes/token.h"

// cat file1 | cat file1
void	init_parser(t_lexer **lex)
{
	t_syntax_tree	**tree;
	t_ast_node	*node;
	t_token		**head;
	e_node_type	type;
	
	tree = ft_calloc(1, sizeof(t_syntax_tree));
	while ((*lex)->token_list)
	{
		head = &(*lex)->token_list;
		while ((*lex)->token_list->type == TOKEN)
		{
			(*head)->
		}
		if ((*lex)->token_list->type == TYPE_PIPE)
		else if ((*lex)->token_list->type == TYPE_AND)
			tok = (*lex)->token_list;
		else if ((*lex)->token_list->type == TYPE_OR)
			tok = (*lex)->token_list;
		else if ((*lex)->token_list->type == TYPE_LSHIFT)
			tok = (*lex)->token_list;
		else if ((*lex)->token_list->type == TYPE_RSHIFT)
			tok = (*lex)->token_list;
		(*lex)->token_list = (*lex)->token_list->next;  
	}
}
