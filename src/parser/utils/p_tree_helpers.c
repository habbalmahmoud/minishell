#include "../../../includes/minishell.h"
#include "../../../includes/ast.h"
#include "../../../includes/token.h"

char	*p_create_cmd_args(char *value, char *args)
{
	char	*whitespace;
	char	*temp;

	if (!args)
		args = ft_strdup(value);
	else
	{
		whitespace = ft_strjoin(args, " ");
		temp = ft_strjoin(whitespace, value);
		free(whitespace);
		free(args);
		args = temp;
	}
	return (args);
}

/*
t_ast_node	*p_redirection_handler_to(t_token **token)
{
	char	*out;
	char	*in;

	in = NULL;
	out = NULL;
	if ((*token)->next && (*token)->next->type == TOKEN)
		out = ft_strdup((*token)->next->value);
	if ((*token)->next && (*token)->next->next)
		(*token) = (*token)->next->next;
	else
	{
		node = p_build_simple_command(str, in, out);
		return (node);
	}
}*/

