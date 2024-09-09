/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_build_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:52:20 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/09 12:31:20 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"

static void	first_part(t_lexer **lex, t_ast_utils **util, int *flag2,
			int *flag)
{
	t_token	*token;

	token = (*lex)->token_list;
	if (token->type == TYPE_MINUS || token->type == TYPE_PLUS
		|| token->type == TYPE_EQUAL
		|| token->type == TOKEN || token->type == TYPE_LPAREN)
		p_parse_simple_command(util, lex);
	else if (token->type == TYPE_RSHIFT || token->type == TYPE_LSHIFT
		|| token->type == TYPE_APPEND || token->type == TYPE_HEREDOC)
	{
		if (p_parse_redirect(util, lex) == 0)
			*flag2 = *flag2 + 1;
		else
			*flag2 = *flag2 + 2;
	}
	else if (token->type == TYPE_PIPE)
		if (p_parse_pipeline(util, lex))
			*flag = 1;
}

static t_ast_node	*second_part(t_lexer **lex, t_ast_utils **util,
		int *flag2, int *flag)
{
	t_token	*token;

	token = (*lex)->token_list;
	if (token)
	{
		if (*flag2 == 0)
			(*lex)->token_list = (*lex)->token_list->next;
		if (token && (token->type == TYPE_AND || token->type == TYPE_OR))
		{
			if (!*flag)
				(*util)->node = p_build_simple_command((*util));
			return ((*util)->node);
		}
		if (*flag2 == 2)
			(*lex)->token_list = NULL;
	}
	return (NULL);
}

t_ast_node	*p_build_pipeline(t_lexer **lex)
{
	t_ast_utils	*util;
	t_ast_node	*node;
	int			flag;
	int			flag2;

	flag = 0;
	flag2 = 0;
	p_init_vars(&util);
	(*lex)->token_list = (*lex)->token_list->next;
	while ((*lex)->token_list)
	{
		flag2 = 0;
		first_part(lex, &util, &flag2, &flag);
		if (second_part(lex, &util, &flag2, &flag))
			return (util->node);
	}
	if (!(util->node))
		util->node = p_build_simple_command(util);
	node = util->node;
	free(util->args);
	free(util);
	return (node);
}
