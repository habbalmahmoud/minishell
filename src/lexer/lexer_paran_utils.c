// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   (*lex)er_paran_utils.c                                :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/05 11:36:58 by nkanaan           #+#    #+#             */
// /*   Updated: 2024/08/07 11:16:28 by mhabbal          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../lib/includes/list.h"
#include "../../includes/token.h"
#include "../../includes/lexer.h"

static int handle_rparen(t_lexer **lex)
{
	if ((*lex)->util->rec_count > 0)
	{
		(*lex)->util->rec_count -= 1;
		return (1);
	}
	return (0);
}

static int prepare_new_token(t_lexer **lex, t_token **token, int len)
{
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
	return (1);
}

static int handle_lparen(t_lexer **lex, t_token **token, int *state, int len)
{
	t_token *c_token;

	if (!prepare_new_token(lex, token, len))
		return (0);

	(*token)->value[(*lex)->util->j++] = TYPE_LPAREN;
	(*token)->type = TYPE_LPAREN;
	(*state) = IN_PARAN;
	(*lex)->util->c_input++;
	ft_lstadd_back((*lex)->child, ft_lstnew((*token)->id));
	(*lex)->util->rec_count += 1;
	ft_lstlast((*(*lex)->child))->lexer = malloc(sizeof(t_lexer));
	ft_lstlast((*(*lex)->child))->lexer->util = malloc(sizeof(t_lex_utils));
	ft_lstlast((*(*lex)->child))->lexer->util->clock = 1;
	ft_lstlast((*(*lex)->child))->lexer->util->rec_count = (*lex)->util->rec_count;
	init_lexer((*lex)->util->c_input, ft_strlen((*lex)->util->c_input),
			   &ft_lstlast((*(*lex)->child))->lexer, &c_token);
	(*lex)->util->c_input += ft_lstlast((*(*lex)->child))->lexer->util->i;

	if (*(*lex)->util->c_input == ')' && (*state) == IN_PARAN)
	{
		(*state) = STATE_ANY;
		(*token)->value[(*lex)->util->j++] = TYPE_RPAREN;
		(*token)->value[(*lex)->util->j] = '\0';
		if (!prepare_new_token(lex, token, len))
			return (0);
	}
	return (1);
}

int handle_paran(t_lexer **lex, t_token **token, int *state, int type)
{
	int len;

	len = ft_strlen((*lex)->util->input);
	if (type == TYPE_RPAREN)
		return (handle_rparen(lex));
	if (type == TYPE_LPAREN)
		return (handle_lparen(lex, token, state, len));
	return (0);
}

// int	handle_paran(t_lexer **lex, t_token **token, int *state, int type)
// {
// 	int len;

// 	len = ft_strlen((*lex)->util->input);
// 	if (type == TYPE_RPAREN && (*lex)->util->rec_count > 0)
// 	{
// 		(*lex)->util->rec_count -= 1;
// 		return (1);
// 	}
// 	if (type == TYPE_LPAREN)
// 	{
// 		int	len;
// 		t_token	*c_token;

// 		len = ft_strlen((*lex)->util->input);
// 		if ((*lex)->util->j > 0)
// 		{
// 			(*token)->value[(*lex)->util->j] = '\0';
// 			(*token)->next = ft_calloc(1, sizeof(t_token));
// 			if ((*token)->next == NULL)
// 				return (0);
// 			init_token((*token)->next, len - (*lex)->util->i, (*token)->id);
// 			*token = (*token)->next;
// 			(*lex)->util->j = 0;
// 		}
// 		(*token)->value[(*lex)->util->j++] = TYPE_LPAREN;
// 		(*token)->type = type;
// 		(*state) = IN_PARAN;
// 		(*lex)->util->c_input++;
// 		ft_lstadd_back((*lex)->child, ft_lstnew((*token)->id));
// 		(*lex)->util->rec_count += 1;
// 		ft_lstlast((*(*lex)->child))->lexer = malloc(sizeof(t_lexer));
// 		ft_lstlast((*(*lex)->child))->lexer->util = malloc(sizeof(t_lex_utils));
// 		ft_lstlast((*(*lex)->child))->lexer->util->clock = 1;
// 		ft_lstlast((*(*lex)->child))->lexer->util->rec_count = (*lex)->util->rec_count;
// 		init_lexer((*lex)->util->c_input, ft_strlen((*lex)->util->c_input),
// 				&ft_lstlast((*(*lex)->child))->lexer, &c_token);
// 		(*lex)->util->c_input += ft_lstlast((*(*lex)->child))->lexer->util->i;
// 		if (*(*lex)->util->c_input == ')' && (*state) == IN_PARAN)	
// 		{
// 			(*state) = STATE_ANY;
// 			(*token)->value[(*lex)->util->j++] = TYPE_RPAREN;
// 			(*token)->value[(*lex)->util->j] = '\0';
// 			(*token)->next = ft_calloc(1, sizeof(t_token));
// 			if ((*token)->next == NULL)
// 				return (0);
// 			init_token((*token)->next, len - (*lex)->util->i, (*token)->id);
// 			*token = (*token)->next;
// 			(*lex)->util->j = 0;
// 		}
// 	}
// 	return (0);
// }












// int	handle_paran(t_lexer **lex, t_token **token, int *state, int type)
// {
// 	if (type == TYPE_RPAREN && (*state) != IN_PARAN && (*lex)->util->rec_count > 0)
// 	{
// 		(*lex)->util->rec_count -= 1;
// 		return (1);
// 	}
// 	// if (type == TYPE_RPAREN && (*state) == STATE_ANY && (*lex)->util->rec_count == 0)
// 	// 	exit(2);
// 	if (type == TYPE_LPAREN)
// 	{
// 		int	len;

// 		len = ft_strlen((*lex)->util->input);
// 		if ((*lex)->util->j > 0)
// 		{
// 			(*token)->value[(*lex)->util->j] = '\0';
// 			(*token)->next = ft_calloc(1, sizeof(t_token));
// 			if ((*token)->next == NULL)
// 				return (0);
// 			*token = (*token)->next;
// 			init_token((*token), len - (*lex)->util->i);
// 			(*lex)->util->j = 0;
// 		}
// 		// printf("ONE: %c\n", (*lex)->util->c);
// 		(*token)->value[(*lex)->util->j++] = TYPE_LPAREN;
// 		(*token)->type = type;
// 		(*state) = IN_PARAN;
// 		(*lex)->util->c_input++;
// 		// if ((*lex)->sub_lex)
// 		// 	printf("%s\n", (*lex)->sub_lex->token_list->value);
// 		printf("%p\n", (*lex)->sub_lex);
// 		int moved = 0;
// 		if ((*lex)->sub_lex)
// 		{
// 			(*lex)->sub_lex->next = malloc(sizeof(t_lexer));
// 			(*lex)->sub_lex->next->util = malloc(sizeof(t_lex_utils));
// 			(*lex)->sub_lex->next->util->clock = 1;
// 			(*lex)->sub_lex->next->util->rec_count = (*lex)->util->rec_count;
// 			moved = 1;
// 		}
// 		else
// 		{
// 				(*lex)->sub_lex = malloc(sizeof(t_lexer));
// 				(*lex)->sub_lex->util = malloc(sizeof(t_lex_utils));
// 				(*lex)->sub_lex->util->clock = 1;
// 				(*lex)->sub_lex->util->rec_count = (*lex)->util->rec_count;
// 		}
// 		(*lex)->util->rec_count += 1;
// 		if (moved == 0)
// 		{
// 			init_lexer((*lex)->util->c_input, ft_strlen((*lex)->util->c_input),
// 					&(*lex)->sub_lex, &(*token)->sub_token);
// 			(*lex)->util->c_input += (*lex)->sub_lex->util->i;
// 		}
// 		else if (moved == 1)
// 		{
// 			init_lexer((*lex)->util->c_input, ft_strlen((*lex)->util->c_input),
// 				&(*lex)->sub_lex->next, &(*token)->sub_token);	
// 				(*lex)->util->c_input += (*lex)->sub_lex->next->util->i;	
// 		}

// 		if ((*lex)->util->clock == 0 && *(*lex)->util->c_input == ')')
// 		{
// 			// printf("	h	\n");
// 			(*state) = STATE_ANY;
// 			(*token)->value[(*lex)->util->j++] = TYPE_RPAREN;
// 			(*token)->value[(*lex)->util->j] = '\0';
// 			(*token)->next = ft_calloc(1, sizeof(t_token));
// 			if ((*token)->next == NULL)
// 				return (0);
// 			(*token) = (*token)->next;
// 			init_token((*token), len - (*lex)->util->i);
// 			(*lex)->util->j = 0;
// 		}
// 		// (*lex)->util->c_input += (*lex)->sub_lex->util->i;
// 		if (*(*lex)->util->c_input == ')' && (*state) == IN_PARAN)	
// 		{
// 			// if ((*lex)->sub_lex->util->rec_count == 0)
// 			(*state) = STATE_ANY;
// 			(*token)->value[(*lex)->util->j++] = TYPE_RPAREN;
// 			(*token)->value[(*lex)->util->j] = '\0';
// 			(*token)->next = ft_calloc(1, sizeof(t_token));
// 			if ((*token)->next == NULL)
// 				return (0);
// 			*token = (*token)->next;
// 			init_token((*token), len - (*lex)->util->i);
// 			(*lex)->util->j = 0;
// 		}
// 		// printf("%s\n", (*lex)->token_list->sub_token->value);
// 	}
// 	return (0);
// }
