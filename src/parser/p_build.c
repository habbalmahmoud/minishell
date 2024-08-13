#include "../../includes/ast.h"
#include "../../includes/token.h"

t_ast_node	*p_build_tree(t_token *token)
{
	t_ast_node	*node;
	t_ast_node	*right;
	char		*args;
	char		**files;

	args = NULL;
	node = NULL;
	right = NULL;
	files = (char **)malloc(2 * sizeof(char *));
	// handle case when < is in the beginning -> if (token == LSHIFT) 
	// before entering the loop and call function that handles this case?
	
	// If type is PAREN save args as word and save position 
	// in the token list to use later
	while (token)
	{
		if (token->type == TOKEN || token->type == TYPE_LPAREN)
			args = p_create_cmd_args(token->value, args);
		else if (token->type == TYPE_RSHIFT)
		{
			if (token->next && token->next->type == TOKEN)
				files[0] = ft_strdup(token->next->value);
			if (token->next && token->next->next)
				token = token->next->next;
			else
			{
				node = p_build_simple_command(args, files[1], files[0]);
				break ;
			}
		}
		else if (token->type == TYPE_LSHIFT)
		{
			if (token->next && token->next->type == TOKEN)
				files[1] = ft_strdup(token->next->value);
			if (token->next && token->next->next)
				token = token->next->next;
			else
			{
				node = p_build_simple_command(args, files[1], files[0]);
				break ;
			}
		}
		if (token->type == TYPE_PIPE)
		{
			node = p_build_simple_command(args, files[1], files[0]);
			free(args);
			args = NULL;
			token = token->next;
			right = p_build_tree(token);
			node = p_build_pipe(node, right);
			break ;
		}
		if (!token->next)
			node = p_build_simple_command(args, files[1], files[0]);
		token = token->next;
	}
	return (node);
}
