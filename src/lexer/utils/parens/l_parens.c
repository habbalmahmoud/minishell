/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_parens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:10:31 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/09 11:10:31 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/lexer.h"

int	handle_paren(t_lexer **lex, t_token **token, int *state, int type)
{
	size_t len;

	len = ft_strlen((*lex)->util->input);
	if (type == TYPE_RPAREN && (*lex)->util->rec_count > 0)
	{
		if ((*lex)->util->clock == 0 && *(*lex)->util->input_ptr == ')')
		{
			(*state) = STATE_ANY;
			(*token)->value[(*lex)->util->j++] = TYPE_RPAREN;
			(*token)->value[(*lex)->util->j] = TYPE_NULL;
			(*token)->next = ft_calloc(1, sizeof(t_token));
			if ((*token)->next == NULL)
				return (0);
			init_token((*token)->next, len - (*lex)->util->i, (*token)->id);
			(*token) = (*token)->next;
			(*lex)->util->j = 0;
			(*lex)->util->input_ptr += l_lstlast((*(*lex)->child))->lexer->util->i;
		}
		else
		{
			(*lex)->util->rec_count -= 1;
			return (1);
		}
	}
	if (type == TYPE_RPAREN && (*state) == STATE_ANY && (*lex)->util->rec_count == 0)
		exit(2);
	if (type == TYPE_LPAREN)
	{
		size_t	len;
		t_token	*c_token;

		len = ft_strlen((*lex)->util->input);
		if ((*lex)->util->j > 0)
		{
			(*token)->value[(*lex)->util->j] = TYPE_NULL;
			(*token)->next = ft_calloc(1, sizeof(t_token));
			if ((*token)->next == NULL)
				return (0);
			init_token((*token)->next, len - (*lex)->util->i, (*token)->id);
			*token = (*token)->next;
			(*lex)->util->j = 0;
		}
		(*token)->value[(*lex)->util->j++] = TYPE_LPAREN;
		(*token)->type = type;
		(*state) = IN_PARAN;
		(*lex)->util->input_ptr++;
		l_lstadd_back((*lex)->child, l_lstnew((*token)->id));
		(*lex)->util->rec_count += 1;
		l_lstlast((*(*lex)->child))->lexer = malloc(sizeof(t_lexer));
		l_lstlast((*(*lex)->child))->lexer->util = malloc(sizeof(t_lex_utils));
		//printf("CLOCK: %d\n", l_lstlast((*(*lex)->child))->lexer->util->clock);
		l_lstlast((*(*lex)->child))->lexer->util->clock = 1;
		l_lstlast((*(*lex)->child))->lexer->util->rec_count = (*lex)->util->rec_count;
		init_lexer((*lex)->util->input_ptr, ft_strlen((*lex)->util->input_ptr),
				&l_lstlast((*(*lex)->child))->lexer, &c_token);
		(*lex)->util->input_ptr += l_lstlast((*(*lex)->child))->lexer->util->i;
		if (*(*lex)->util->input_ptr == ')' && (*state) == IN_PARAN)	
		{
			//printf("PTR: %s\n", (*lex)->util->input_ptr);
			//printf("SECOND\n");
			(*state) = STATE_ANY;
			(*token)->value[(*lex)->util->j++] = TYPE_RPAREN;
			(*token)->value[(*lex)->util->j] = TYPE_NULL;
			(*token)->next = ft_calloc(1, sizeof(t_token));
			if ((*token)->next == NULL)
				return (0);
			init_token((*token)->next, len - (*lex)->util->i, (*token)->id);
			*token = (*token)->next;
			(*lex)->util->j = 0;
		}
	}
	return (0);
}
