/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:30:04 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/30 16:30:04 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/token.h"
#include <glob.h>
#include <string.h>

static void	init_vars(int len, t_lexer *lex, t_token *token)
{
	lex->token_list = ft_calloc(1, sizeof(t_token));
	token = lex->token_list;
	init_token(token, len);
}


int	init_lexer(char *input, int len, t_lexer *lex)
{
 	int	i;
 	int	j;
 	int	flag;
 	t_token	*token;

 	i = 0;
 	j = 0;
 	flag = ANY;
 	init_vars(len, lex, token);
}

static void	handle_wildcards(t_token *token, int count, char **hits)
{		
        t_token *saved = token->next;

        free(token->value);
        token->value = malloc(ft_strlen(hits[0]) + 1);
        strcpy(token->value, hits[0]);

		int i;
		for (i = 1; i < count; i++)
		{
			token->next = malloc(sizeof(t_token));
			init_token(token->next, ft_strlen(hits[i]));
			token = token->next;
			token->type = FT_TOKENIZED;
			ft_strcpy(token->value, hits[i]);
		}

		token->next = saved;
			for (i = 0; i < count; i++) {
				free(hits[i]);
		}
    	free(hits);
}

static char	*remove_quotes(t_token *token)
{
	char* clean;

	clean = ft_calloc(1, ft_strlen(token->value) + 1);
	clean_input(token->value, clean);
	free(token->value);
	return(clean);
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
