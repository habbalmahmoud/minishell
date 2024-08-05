/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:30:04 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/05 11:38:24 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	lex_words(t_lexer *lex, t_token *token, int type);
static void	lex_next(t_lexer *lex, t_token **token, int type, int len);
static void	handle_quote_state(t_lexer *lex, t_token **token, int type, int *state);
static void	terminate_token(t_lexer *lex, t_token **token, int type);

void	tokenize(t_lexer *lex, t_token **token, int type, int *state)
{
	int	len;

	len = ft_strlen(lex->util->input);
	if ((*state) == STATE_ANY)
	{
		if (type == TYPE_QUOTE || TYPE_DQUOTE)
			handle_quote_state(lex, token, type, state);
		if (type == TYPE_ESC || type == TYPE_WORD)
			lex_words(lex, (*token), type);
		else if (type == TYPE_SPACE)
			lex_next(lex, token, type, len);
		else if (type == TYPE_SEMI || type == TYPE_LSHIFT
			|| type == TYPE_RSHIFT)
			lex_next(lex, token, type, len);
		else if (type == TYPE_AMPERSAND)
			lex_and(lex, token, state, type);
		else if (type == TYPE_PIPE)
			lex_or(lex, token, state, type);
	}
	else if ((*state) == IN_QUOTES || (*state) == IN_DQUOTES)
		handle_quote_state(lex, token, type, state);
	else if ((*state) == IN_AND)
	{
		handle_and_state(lex, token, type, len);
		(*state) = STATE_ANY;
	}
	else if ((*state) == IN_OR)
	{
		handle_or_state(lex, token, type, len);
		(*state) = STATE_ANY;
	}
	if (type == TYPE_NULL)
		terminate_token(lex, token, type);
}

static void	lex_next(t_lexer *lex, t_token **token, int type, int len)
{
	if (lex->util->j > 0)
	{
		(*token)->value[lex->util->j] = '\0';
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		*token = (*token)->next;
		init_token((*token), len - lex->util->i);
		lex->util->j = 0;
	}
	if (type != TYPE_SPACE)
	{
		(*token)->value[0] = type;
		(*token)->value[1] = '\0';
		(*token)->type = type;
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return;
		*token = (*token)->next;
		init_token(*token, len - lex->util->i);
	}
}

static void	handle_quote_state(t_lexer *lex, t_token **token, int type, int *state)
{
	if (type == TYPE_QUOTE)
	{
		(*state) = IN_QUOTES;
		(*token)->value[lex->util->j++] = TYPE_QUOTE;
		(*token)->type = TOKEN;
	}
	else if (type == TYPE_DQUOTE)
	{
		(*state) = IN_DQUOTES;
		(*token)->value[lex->util->j++] = TYPE_DQUOTE;
		(*token)->type = TOKEN;
	}
	else if ((*state) == IN_DQUOTES)
	{
		(*token)->value[lex->util->j++] = lex->util->c;
		if (type == TYPE_DQUOTE)
			(*state) = STATE_ANY;
	}
	else if ((*state) == IN_QUOTES)
	{
		(*token)->value[lex->util->j++] = lex->util->c;
		if (type == TYPE_QUOTE)
			(*state) = STATE_ANY;
	}
}

static void	terminate_token(t_lexer *lex, t_token **token, int type)
{

	if (lex->util->j > 0)
	{
		(*token)->value[lex->util->j] = '\0';
		lex->util->j = 0;
	}
}

static void	lex_words(t_lexer *lex, t_token *token, int type)
{
	if (type == TYPE_ESC)
	{
		token->value[lex->util->j++] = lex->util->input[++(lex->util->i)];
		token->type = TOKEN;
	}
	else if (type == TYPE_WORD)
	{
		token->value[lex->util->j++] = lex->util->c;
		token->type = TOKEN;
	}
}
//////////////////// BRAINSTROM ///////////////////////
/* 
 * INIT LEXER => struct init and allocation + init_token()
 * LEX_NEXT (ITERATE WHEN TOKEN ASSIGNED) => iterate by index in 
 *					     struct
 *					       |
 *				   t_lexer *lexer->index += 1;			   
 * LEX_BY_ID => TBD TBD TBD 
 *
 * LEX_PEAK => SET FLAG TO PEAK = 0
 *		IF PEAK == 1 => look ahead in the str (INPUT).
 *		CHECK IF FLAG SET LOCAL OR IN STRUCT ??
 * -------------------------------------
 *  ASSIGN TOKENS => basic switch case (if else due to norme) 
 *		      Special cases:
 *				echo (TAKE ALL ARGS AFTER AS ONE TOKEN???)
 *				"|" (PIPE IN QUOTES)
 *				ALL QUOTES (DISREGARD FOR LEXER V1)
 *
 * COMMAND EXAMPLES: 
 *		"cat file1" => unkown cmd
 *		echo 'hello' | cat -e => hello$
 *		echo -n 'hello' | cat -e => hello
 * TOKEN---
 *	  |
 *	  => INIT_TOKEN = ALLOCATE MEMORY (CALLOC) + STRCUT INIT 
 *		=> ASSIGN_TOKEN ((TOKEN_TYPE) -- (TOKEN_VALUE))
 *			=> COMMAND + FILES SET AS STRING (WORD) TYPE TOK
 *
 * */
//////////////////// AST TEMPLATE ///////////////////////
/*
                 __ PIPE__
                     ___/              \____
                    /                       \
            COMMAND                    __ PIPE _
          /        \                  /         \
    ARGUMENTS   REDIRECTIONS	    CMD        _ CMD__
        |          |     |           |           /    \
       cat        <<     >       ARGUMENTS    ARGUMENTS	    REDIR
                   |     |         |   |      |   |   |        |
                 "..."  file      wc  -c      tr  -d " "       >
                                                               |
                                                             file2
*/
