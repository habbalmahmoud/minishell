/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ampersand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:07:27 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/08 17:20:20 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include "../../../../includes/lexer.h"

static void	l_handler_skip(t_lexer *lex, t_token **token, int type, int **state)
{
	size_t	len;

	(void)type;
	len = ft_strlen(lex->util->input);
	(*token)->value[lex->util->j] = '\0';
	(*token)->next = ft_calloc(1, sizeof(t_token));
	if ((*token)->next == NULL)
		return ;
	init_token((*token)->next, len - lex->util->i, (*token)->id);
	*token = (*token)->next;
	lex->util->j = 0;
	**state = STATE_ANY;
}

void	l_tokenize_ampersand(t_lexer *lex, t_token **token,
			int *state, int type)
{
	int	len;

	len = ft_strlen(lex->util->input);
	if (lex->util->j > 0)
	{
		(*token)->value[lex->util->j] = '\0';
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
	}
	(*token)->value[lex->util->j++] = type;
	(*token)->type = type;
	(*state) = IN_AND;
}

void	l_handler_ampersand(t_lexer *lex, t_token **token, int type, int *state)
{
	size_t	len;

	len = ft_strlen(lex->util->input);
	if (type == TYPE_AMPERSAND)
	{
		(*token)->value[lex->util->j++] = type;
		(*token)->value[lex->util->j] = '\0';
		(*token)->type = TYPE_AND;
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
	}
	else if (type != TYPE_AMPERSAND)
	{
		l_handler_skip(lex, token, type, &state);
		l_tokenize(lex, token, type, state);
	}
}
