/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_build_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:52:25 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/08 13:48:20 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"

static void	first_part(t_token **token, t_ast_utils **util, int *flag2)
{
	if ((*token)->type == TYPE_MINUS || (*token)->type == TYPE_PLUS
		|| (*token)->type == TYPE_EQUAL || (*token)->type == TOKEN
		|| (*token)->type == TYPE_LPAREN)
		p_parse_simple_command(util, (*token));
	else if ((*token)->type == TYPE_RSHIFT || (*token)->type == TYPE_LSHIFT
		|| (*token)->type == TYPE_APPEND || (*token)->type == TYPE_HEREDOC)
	{
		if (p_parse_redirect(util, token) == 0)
			*flag2 = *flag2 + 1;
		else
			*flag2 = *flag2 + 2;
	}
	else if ((*token)->type == TYPE_PIPE)
		if (p_parse_pipeline(util, token))
			(*util)->in_pipe = 1;
}

static int	second_part(t_token **token, t_ast_utils **util, int *flag2)
{
	if ((*token)->type == TYPE_AND || (*token)->type == TYPE_OR)
		if (p_parse_operators(util, token))
			return (0);
	if (*flag2 == 0)
		(*token) = (*token)->next;
	else if (*flag2 == 2)
		(*token) = (*token)->next;
	return (1);
}

t_ast_node	*p_build_tree(t_token *token)
{
	t_ast_utils	*util;
	t_ast_node	*node;
	int			flag2;

	flag2 = 0;
	p_init_vars(&util);
	while (token)
	{
		flag2 = 0;
		first_part(&token, &util, &flag2);
		if (!second_part(&token, &util, &flag2))
			break ;
	}
	if (!util->node)
		util->node = p_build_simple_command(util);
	node = util->node;
	free(util->args);
	free(util);
	return (node);
}
