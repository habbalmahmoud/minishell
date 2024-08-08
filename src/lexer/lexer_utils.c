/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:02:56 by mhabbal           #+#    #+#             */
/*   Updated: 2024/08/08 14:03:41 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/token.h"
#include "../../includes/lexer.h"

void	handle_and_state(t_lexer *lex, t_token **token, int type, int len)
{
	if (type == TYPE_AMPERSAND)
	{
		(*token)->value[lex->util->j++] = type;
		(*token)->value[lex->util->j] = '\0';
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
	}
	else if (type != TYPE_AMPERSAND)
	{
		(*token)->value[lex->util->j] = '\0';
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
		if (type != TYPE_SPACE)
			(*token)->value[lex->util->j++] = lex->util->c;
	}
}

void	lex_and(t_lexer *lex, t_token **token, int *state, int type)
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

void	handle_or_state(t_lexer *lex, t_token **token, int type, int len)
{
	if (type == TYPE_PIPE)
	{
		(*token)->value[lex->util->j++] = type;
		(*token)->value[lex->util->j] = '\0';
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
	}
	else if (type != TYPE_PIPE)
	{
		(*token)->value[lex->util->j] = '\0';
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
		if (type != TYPE_SPACE)
			(*token)->value[lex->util->j++] = lex->util->c;
	}
}

void	lex_or(t_lexer *lex, t_token **token, int *state, int type)
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
	(*state) = IN_OR;
}