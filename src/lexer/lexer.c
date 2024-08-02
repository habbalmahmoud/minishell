/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:30:04 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/02 16:00:07 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_vars(char *input, int len, t_lexer *lex, t_token *token);
static void	handle_state_in(t_lexer *lex, t_token *token, int type, int *state);
static void	handle_state_out(t_lexer *lex, t_token *token, int type, int *state);
static void	lexer_skip(int size, int type, t_token *token, t_lexer *lex);
static void	lexer_next(int size, int type, t_token *token, int i);


int init_lexer(char *input, int len, t_lexer *lex) {
    int state = STATE_ANY;
    t_token *token;
    int i = 0;
    int j = 0;
    char c;

    lex->token_list = malloc(sizeof(t_token));
    token = lex->token_list;
    init_token(token, len);

    while (input[i] != '\0') {
        c = input[i];
        int type = assign_type(c);

        if (state == STATE_ANY) {
            if (type == TYPE_QUOTE) {
                state = IN_QUOTES;
                token->value[j++] = TYPE_QUOTE;
                token->type = TOKEN;
            } else if (type == TYPE_DQUOTE) {
                state = IN_DQUOTES;
                token->value[j++] = TYPE_DQUOTE;
                token->type = TOKEN;
            } else if (type == TYPE_ESC) {
                token->value[j++] = input[++i];
                token->type = TOKEN;
            } else if (type == TYPE_WORD) {
                token->value[j++] = c;
                token->type = TOKEN;
            } else if (type == TYPE_SPACE) {
                if (j > 0) {
                    token->value[j] = '\0';
                    token->next = ft_calloc(1, sizeof(t_token));
                    token = token->next;
                    init_token(token, len - i);
                    j = 0;
                }
            } else if (type == TYPE_SEMI || type == TYPE_PIPE || type == TYPE_LSHIFT || type == TYPE_RSHIFT) {
                if (j > 0) {
                    token->value[j] = '\0';
                    token->next = ft_calloc(1, sizeof(t_token));
                    token = token->next;
                    init_token(token, len - i);
                    j = 0;
                }
                token->value[0] = type;
                token->value[1] = '\0';
                token->type = type;
                token->next = ft_calloc(1, sizeof(t_token));
                token = token->next;
                init_token(token, len - i);
            }
        } else if (state == IN_DQUOTES) {
            token->value[j++] = c;
            if (type == TYPE_DQUOTE) {
                state = STATE_ANY;
            }
        } else if (state == IN_QUOTES) {
            token->value[j++] = c;
            if (type == TYPE_QUOTE) {
                state = STATE_ANY;
            }
        }
        if (type == TYPE_NULL) {
            if (j > 0) {
                token->value[j] = '\0';
                j = 0;
            }
        }
        i++;
    }

    if (j > 0) { // Handle remaining characters
        token->value[j] = '\0';
    }

    token = lex->token_list;
    int k = 0;
    while (token) {
        if (token->type == TOKEN) {
            int hits;
            char **matches = ft_glob(token->value, &hits);
            if (hits > 0) {
                k += hits;
                handle_wildcards(token, hits, matches);
            } else {
                token->value = remove_quotes(token);
                k++;
            }
        }
        token = token->next;
    }
    lex->count = k;
    return k;
}

static void	lexer_next(int size, int type, t_token *token, int i)
{
	token->value[0] = type;
	token->value[1] = 0;
	token->type = type;
	token->next = ft_calloc(1, sizeof(t_token));
	token = token->next;
	init_token(token, size - i);
}

static void	lexer_skip(int size, int type, t_token *token, t_lexer *lex)
{
	int	*i;
	int	*j;

	i = &lex->util->i;
	j = &lex->util->j;
	if (type == TYPE_ESC)
	{
		token->value[(*j)++] = lex->util->str[++(*i)];
		token->type = TOKEN;
	}
	if (type == TYPE_WORD)
	{
		token->value[(*j)++] = lex->util->c;
		token->type = TOKEN;
	}
}

static void	handle_state_in(t_lexer *lex, t_token *token, int type, int *state)
{
	int	*j;

	j = &lex->util->j;
	if (type == TYPE_QUOTE)
	{
		(*state) = IN_QUOTES;
		token->value[(*j)++] = TYPE_QUOTE;
		token->type = TOKEN;
	}
	if (type == TYPE_DQUOTE)
	{
		(*state) = IN_DQUOTES;
		token->value[(*j)++] = TYPE_DQUOTE;
		token->type = TOKEN;
	}
}

static void	handle_state_out(t_lexer *lex, t_token *token, int type, int *state)
{
	int	*j;

	j = &lex->util->j;
	if ((*state) == IN_DQUOTES)
	{
		token->value[(*j)++] = lex->util->c;
		if (type = TYPE_DQUOTE)
			(*state) = STATE_ANY;
	}
	if ((*state) == IN_QUOTES)
	{
		token->value[(*j)++] = lex->util->c;
		if (type = TYPE_QUOTE)
			(*state) = STATE_ANY;
	}
}

static void	init_vars(char *input, int len, t_lexer *lex, t_token *token)
{
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
