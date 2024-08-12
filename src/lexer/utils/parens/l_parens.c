/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_parens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:10:31 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/12 15:56:55 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/lexer.h"

// static int handle_rparen(t_lexer **lex)
// {
// 	if ((*lex)->util->rec_count > 0)
// 	{
// 		(*lex)->util->rec_count -= 1;
// 		return (1);
// 	}
// 	return (0);
// }

// static int prepare_new_token(t_lexer **lex, t_token **token, int len)
// {
// 	if ((*lex)->util->j > 0)
// 	{
// 		(*token)->value[(*lex)->util->j] = '\0';
// 		(*token)->next = ft_calloc(1, sizeof(t_token));
// 		if ((*token)->next == NULL)
// 			return (0);
// 		init_token((*token)->next, len - (*lex)->util->i, (*token)->id);
// 		*token = (*token)->next;
// 		(*lex)->util->j = 0;
// 	}
// 	return (1);
// }

// static int handle_lparen(t_lexer **lex, t_token **token, int *state, int len)
// {
// 	t_token *c_token;

// 	if (!prepare_new_token(lex, token, len))
// 		return (0);

// 	(*token)->value[(*lex)->util->j++] = TYPE_LPAREN;
// 	(*token)->type = TYPE_LPAREN;
// 	(*state) = IN_PARAN;
// 	(*lex)->util->input_ptr++;
// 	l_lstadd_back((*lex)->child, l_lstnew((*token)->id));
// 	(*lex)->util->rec_count += 1;
// 	l_lstlast((*(*lex)->child))->lexer = malloc(sizeof(t_lexer));
// 	l_lstlast((*(*lex)->child))->lexer->util = malloc(sizeof(t_lex_utils));
// 	l_lstlast((*(*lex)->child))->lexer->util->clock = 1;
// 	l_lstlast((*(*lex)->child))->lexer->util->rec_count = (*lex)->util->rec_count;
// 	init_lexer((*lex)->util->input_ptr, ft_strlen((*lex)->util->input_ptr),
// 			   &l_lstlast((*(*lex)->child))->lexer, &c_token);
// 	(*lex)->util->input_ptr += l_lstlast((*(*lex)->child))->lexer->util->i;

// 	if (*(*lex)->util->input_ptr == ')' && (*state) == IN_PARAN)
// 	{
// 		(*state) = STATE_ANY;
// 		(*token)->value[(*lex)->util->j++] = TYPE_RPAREN;
// 		(*token)->value[(*lex)->util->j] = '\0';
// 		if (!prepare_new_token(lex, token, len))
// 			return (0);
// 	}
// 	return (1);
// }

// int handle_paren(t_lexer **lex, t_token **token, int *state, int type)
// {
// 	int len;

// 	len = ft_strlen((*lex)->util->input);
// 	if (type == TYPE_RPAREN)
// 		return (handle_rparen(lex));
// 	if (type == TYPE_LPAREN)
// 		return (handle_lparen(lex, token, state, len));
// 	return (0);
// }
int	handle_paren(t_lexer **lex, t_token **token, int *state, int type)
{
	int len;

	len = ft_strlen((*lex)->util->input);
	if (type == TYPE_RPAREN && (*lex)->util->rec_count > 0)
	{
		// printf("%d\n", (*lex)->util->rec_count);
		// (*lex)->util->rec_count -= 1;
		return (1);
	}
	if (type == TYPE_LPAREN)
	{
		
		t_token	*c_token;

		
		if ((*lex)->util->j > 0)
		{
			(*token)->value[(*lex)->util->j] = '\0';
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
		l_lstlast((*(*lex)->child))->lexer = malloc(sizeof(t_lexer));
		l_lstlast((*(*lex)->child))->lexer->util = malloc(sizeof(t_lex_utils));
		l_lstlast((*(*lex)->child))->lexer->util->clock = 1;
		l_lstlast((*(*lex)->child))->lexer->util->rec_count = (*lex)->util->rec_count + 1;
		init_lexer((*lex)->util->input_ptr, ft_strlen((*lex)->util->input_ptr),
				&l_lstlast((*(*lex)->child))->lexer, &c_token);
		(*lex)->util->i += l_lstlast((*(*lex)->child))->lexer->util->i;
		(*lex)->util->input_ptr += l_lstlast((*(*lex)->child))->lexer->util->i;
		if (*(*lex)->util->input_ptr == ')' && (*state) == IN_PARAN)	
		{
			(*state) = STATE_ANY;
			(*token)->value[(*lex)->util->j++] = TYPE_RPAREN;
			(*token)->value[(*lex)->util->j] = '\0';
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