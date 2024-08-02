/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:30:04 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/02 13:01:33 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*init_vars(char *input, int len, t_lexer *lex, t_token *token)
{
	lex->token_list = malloc(sizeof(t_token));
	token = lex->token_list;
	lex->util = malloc(sizeof(t_lex_utils));
	lex->util->i = 0;
	lex->util->j = 0;
	lex->util->input = input;
	return (token);
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

int init_lexer(char *input, int len, t_lexer *lex)
{
	int	state;
	int	type;
	t_token	*token;

	state = STATE_ANY;
	token = init_vars(input, len, lex, token);
	init_token(token, len);
	while (input[lex->util->i] != '\0') 
	{
		lex->util->c = input[lex->util->i];
		type = assign_type(lex->util->c);
		if (state == STATE_ANY)
		{
			if (type == TYPE_QUOTE)
			{
				state = IN_QUOTES;
				token->value[lex->util->j++] = TYPE_QUOTE;
				token->type = TOKEN;
			}
			else if (type == TYPE_DQUOTE)
			{
				state = IN_DQUOTES;
				token->value[lex->util->j++] = TYPE_DQUOTE;
				token->type = TOKEN;
			}
			else if (type == TYPE_ESC || type == TYPE_WORD)
				lex_words(lex, token, type);
			else if (type == TYPE_SPACE)
				lex_next(lex, &token, type, len);
			else if (type == TYPE_SEMI || type == TYPE_PIPE || type == TYPE_LSHIFT || type == TYPE_RSHIFT)
				lex_next(lex, &token, type, len);
		}
		else if (state == IN_DQUOTES)
		{
			token->value[lex->util->j++] = lex->util->c;
			if (type == TYPE_DQUOTE)
				state = STATE_ANY;
		}
		else if (state == IN_QUOTES)
		{
			token->value[lex->util->j++] = lex->util->c;
			if (type == TYPE_QUOTE)
				state = STATE_ANY;
		}
		if (type == TYPE_NULL)
		{
			if (lex->util->j > 0)
			{
				token->value[lex->util->j] = '\0';
				lex->util->j = 0;
			}
		}
		lex->util->i++;
	}
	if (lex->util->j > 0)
		token->value[lex->util->j] = '\0';
	token = lex->token_list;
	int k = 0;
	while (token)
	{
		if (token->type == TOKEN)
		{
			int hits;
			char **matches = ft_glob(token->value, &hits);
			if (hits > 0)
			{
				k += hits;
				handle_wildcards(token, hits, matches);
			}else{
				token->value = remove_quotes(token);
				k++;
			}
		}
        token = token->next;
	}
	lex->count = k;
	return k;
}


/*
void	handle_token_state(t_lexer *lex, t_token **token, int type, int len) {
    if (lex->util->j > 0) {
        (*token)->value[lex->util->j] = '\0';
        (*token)->next = ft_calloc(1, sizeof(t_token));
        if ((*token)->next == NULL) {
            return;
        }
        *token = (*token)->next;
        init_token(*token, len - lex->util->i);
        lex->util->j = 0;
    }

} */
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
