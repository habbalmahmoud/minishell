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

int	p_parse_redirect_to(t_ast_utils **util, t_token **token)
{
		if ((*token)->next && (*token)->next->type == TOKEN)
			(*util)->files[0] = ft_strdup((*token)->next->value);
		if ((*token)->next && (*token)->next->next)
			(*token) = (*token)->next->next;
		else
		{
			(*util)->node = p_build_simple_command((*util));
			return (1);
		}
	return (0);
}

int	p_parse_redirect_from(t_ast_utils **util, t_token **token)
{
		if ((*token)->next && (*token)->next->type == TOKEN)
			(*util)->files[1] = ft_strdup((*token)->next->value);
		if ((*token)->next && (*token)->next->next)
			(*token) = (*token)->next->next;
		else
		{
			(*util)->node = p_build_simple_command((*util));
			return (1);
		}
	return (0);
}

t_ast_node	*p_build_pipeline(t_token **token)
{
	t_ast_utils	*util;
	int		flag;
	int		flag2 = 0;

	flag = 0;
	p_init_vars(&util);
	while ((*token))
	{
		flag2 = 0;
		if ((*token)->type == TOKEN || (*token)->type == TYPE_LPAREN)
			p_parse_simple_command(&util, (*token));
		else if ((*token)->type == TYPE_RSHIFT || (*token)->type == TYPE_LSHIFT)
		{
			if (p_parse_redirect(&util, token) == 0)
				flag2 = 1;
			else
				flag2 = 2;
		}
		else if ((*token)->type == TYPE_PIPE)
			if (p_parse_pipeline(&util, token))
				flag = 1;
		if (flag2 == 0)
			(*token) = (*token)->next; 
		if ((*token) && ((*token)->type == TYPE_AND || (*token)->type == TYPE_OR))
		{
			if (!flag)
				util->node = p_build_simple_command(util);
			return (util->node);
		}
		if (flag2 == 2)
			(*token) = NULL;
	}
	if (!(util->node))
		util->node = p_build_simple_command(util);
	return (util->node);
}





