# include "../../includes/ast.h"

// cat file1 | cat file1
void	init_parser(t_lexer **lex)
{
	t_tree	**tree;
	
	tree = ft_calloc(1, sizeof(t_tree));
	while ((*lex)->token_list)
	{
		p_build_tree((*lex)->token_list, (*tree));
		(*lex)->token_list = (*lex)->token_list->next;
	}
}
