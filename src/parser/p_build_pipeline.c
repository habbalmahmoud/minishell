#include "../../includes/ast.h"
#include "../../includes/token.h"

int	p_parse_pipeline(t_ast_utils **util, t_token *token)
{
	if (token->type == TYPE_PIPE)
	{
		(*util)->node = p_build_simple_command((*util));
		free((*util)->args);
		(*util)->args = NULL;
		(*util)->right = p_build_pipeline(token->next);
		(*util)->node = p_build_separator((*util)->node, (*util)->right, token->type);
		return (1);
	}
	else
		return (0);
}

t_ast_node	*p_build_pipeline(t_token *token)
{
	t_ast_utils	*util;

	p_init_vars(&util);
	while (token)
	{
		if (token->type == TOKEN || token->type == TYPE_LPAREN
			|| token->type == TYPE_RSHIFT || token->type == TYPE_RSHIFT)
			if (p_parse_simple_command(&util, token))
				break ;
		if (token->type == TYPE_PIPE)
		{
			util->node = p_build_simple_command(util);
			free(util->args);
			util->args = NULL;
			util->right = p_build_pipeline(token->next);
			util->node = p_build_separator(util->node, util->right, token->type);
		}
		token = token->next; 
		if (token && (token->type == TYPE_AND || token->type == TYPE_OR))
		{
			util->node = p_build_simple_command(util);
			return (util->node);
		}
	}
	if (!(util->node))
	{
		util->node = p_build_simple_command(util);
		return (util->node);
	}
	return (util->node);
}

