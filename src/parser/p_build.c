#include "../../includes/ast.h"
#include "../../includes/token.h"

t_ast_node	*p_build_pipeline(t_token *token)
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
	
	// If type is PAREN save args as normal word and save position 
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
			right = p_build_pipeline(token);
			node = p_build_pipe(node, right);
			break ;
		}
		if (!token->next)
		{
			node = p_build_simple_command(args, files[1], files[0]);
			return (node);
		}
		token = token->next; 
		if (token && (token->type == TYPE_AND || token->type == TYPE_OR))
		{
			node = p_build_simple_command(args, files[1], files[0]);
			return (node);
		}
	}
	return (node);
}


t_ast_node	*p_build_sep(t_ast_node *left, t_ast_node *right, int type)
{
	t_ast_node *node;
	char	*sep;

	node = ft_calloc(1, sizeof(t_ast_node));
	node->left = left;
	node->right = right;
	node->type = ASSIGN_TYPE(type);
	sep = ASSIGN(type);
	node->args = ft_split(sep, ' ');
	return (node);
}

t_ast_node	*p_build_tree(t_token *token)
{
	t_ast_node	*node;
	t_ast_node	*right;
	char		*args;
	char		**files;
	int flag = 0;

	// root = ft_calloc(1, sizeof(t_ast_node));
	args = NULL;
	node = NULL;
	right = NULL;
	files = (char **)malloc(2 * sizeof(char *));
	// handle case when < is in the beginning -> if (token == LSHIFT) 
	// before entering the loop and call function that handles this case?
	// also check what < as first word does
	
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
			right = p_build_pipeline(token);
			node = p_build_pipe(node, right);
			flag = 1;
		}
		if (token->type == TYPE_AND || token->type == TYPE_OR)
		{
			if (!flag)
				node = p_build_simple_command(args, files[1], files[0]);
			free(args);
			args = NULL;
			right = p_build_tree(token->next);
			node = p_build_sep(node, right, token->type);
			break ;
		}
		token = token->next;
	}
	if (!node)
		node = p_build_simple_command(args, files[1], files[0]);
	return (node);
}


///       &&
/// cmd         cmd


//    cmd

// cat file1 | cat file2

//   |

//  &&
// |
 
