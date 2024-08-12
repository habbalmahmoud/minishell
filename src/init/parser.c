# include "../../includes/ast.h"

// cat file1 | cat file1
void	init_parser(t_lexer **lex)
{
	t_tree	**tree;
	
	tree = ft_calloc(1, sizeof(t_tree));
	while ((*lex)->token_list)
	{
		(void)tree;
		printf("%s\n", (*lex)->token_list->value);
		(*lex)->token_list = (*lex)->token_list->next;
	}
}
