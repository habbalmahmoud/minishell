#include "../../../../includes/ast.h"
#include "../../../../includes/token.h"

int	p_parse_simple_command(t_ast_utils **util, t_token *token)
{

	if (token->type == TYPE_LPAREN)
	{
		(*util)->sub = &token->sub_lexer;
		(*util)->args = p_create_cmd_args(token->value, (*util)->args);
	}
	if (token->type == TOKEN)
		(*util)->args = p_create_cmd_args(token->value, (*util)->args);
	else if (token->type == TYPE_RSHIFT)
	{
		if (token->next && token->next->type == TOKEN)
			(*util)->files[0] = ft_strdup(token->next->value);
		if (token->next && token->next->next)
			token = token->next->next;
		else
		{
			(*util)->node = p_build_simple_command((*util));
			return (1);
		}
	}
	else if (token->type == TYPE_LSHIFT)
	{
		if (token->next && token->next->type == TOKEN)
			(*util)->files[1] = ft_strdup(token->next->value);
		if (token->next && token->next->next)
			token = token->next->next;
		else
		{
			(*util)->node = p_build_simple_command((*util));
			return (1);
		}
	}
	return (0);
}
