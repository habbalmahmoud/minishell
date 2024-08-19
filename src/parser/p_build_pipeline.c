/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_build_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:52:20 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/19 11:52:21 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"

t_ast_node	*p_build_pipeline(t_token **token)
{
	t_ast_utils	*util;
	int		flag;

	flag = 0;
	p_init_vars(&util);
	while ((*token))
	{
		if ((*token)->type == TOKEN || (*token)->type == TYPE_LPAREN
			|| (*token)->type == TYPE_RSHIFT || (*token)->type == TYPE_RSHIFT)
			if (p_parse_simple_command(&util, token))
				break ;
		if ((*token)->type == TYPE_PIPE)
			if (p_parse_pipeline(&util, token))
				flag = 1;
		(*token) = (*token)->next; 
		if ((*token) && ((*token)->type == TYPE_AND || (*token)->type == TYPE_OR))
		{
			if (!flag)
				util->node = p_build_simple_command(util);
			return (util->node);
		}
	}
	if (!(util->node))
		util->node = p_build_simple_command(util);
	return (util->node);
}
