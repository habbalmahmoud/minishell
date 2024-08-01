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

// static void	init_vars(int len, t_lexer *lex, t_token *token)
// {
	
// 	lex->token_list = ft_calloc(1, sizeof(t_token));
// 	token = lex->token_list;
// 	init_token(token, len);
// }


// void	lex_luther(char *input, int len, t_lexer *lex)
// {
// 	int	i;
// 	int	j;
// 	int	flag;
// 	t_token	*token;

// 	i = 0;
// 	j = 0;
// 	flag = ANY;
// 	init_vars(len, lex, token);
	

// }

static void	handle_wildcards(t_token *token, int count, char **hits)
{		
        t_token *saved = token->next;

        // Replace the current token with the first one
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





int lexer_build(char* input, int size, t_lexer *lexerbuf)
{
	if (lexerbuf == NULL)
		return -1;
	
	if (size == 0) {
		lexerbuf->count = 0;
		return 0;
	}
	
	lexerbuf->token_list = ft_calloc(1, (sizeof(t_token)));
	
	// allocate the first token
	t_token *token = lexerbuf->token_list;
	init_token(token, size);
	
	int i = 0;
	int j = 0, ntemptok = 0;
	
	char c;
	int state = ANY;
	
	do
	{
		c = input[i];		
		int chtype = assign_type(c);
		
		if (state == ANY)
		{
		switch (chtype) 
			{
				case QUOTE:
					state = INSIDE_QUOTES;
					token->value[j++] = QUOTE;
					token->type = FT_TOKENIZED;
					break;
					
				case DOUBLE_QUOTE:
					state = INSIDE_DQUOTES;
					token->value[j++] = DOUBLE_QUOTE;
					token->type = FT_TOKENIZED;
					break;
					
				case ESC:
					token->value[j++] = input[++i];
					token->type = FT_TOKENIZED;
					break;
					
				case WORD:
					token->value[j++] = c;
					token->type = FT_TOKENIZED;
					break;
					
				case SPACE:
					if (j > 0) {
						token->value[j] = 0;
						token->next = malloc(sizeof(t_token));
						token = token->next;
						init_token(token, size - i);
						j = 0;
					}
					break;

				case SEMI:
				case LSHIFT:
				case RSHIFT:
				case AMPERSAND:
				case PIPE:
					
					// end the token that was being read before
					if (j > 0) {
						token->value[j] = 0;
						token->next = malloc(sizeof(t_token));
						token = token->next;
						init_token(token, size - i);
						j = 0;
					}
					
					// next token
					token->value[0] = chtype;
					token->value[1] = 0;
					token->type = chtype;
					
					token->next = malloc(sizeof(t_token));
					token = token->next;
					init_token(token, size - i);
					break;
			}
		}
		else if (state == INSIDE_DQUOTES) {
			token->value[j++] = c;
			if (chtype == DOUBLE_QUOTE)
				state = ANY;
			
		}
		else if (state == INSIDE_QUOTES) {
			token->value[j++] = c;
			if (chtype == QUOTE)
				state = ANY;
		}
		
		if (chtype == FT_NULL) {
			if (j > 0) {
				token->value[j] = FT_NULL;
				ntemptok++;
				j = 0;
			}
		}
		i++;
	} while (c != '\0');
	token = lexerbuf->token_list;
	int k = 0;
	while (token != NULL) 
		{
			if (token->type == FT_TOKENIZED)
			{
				int num_matches;
				char **matches = ft_glob(token->value, &num_matches);
				if (num_matches > 0)
				{
					k += num_matches;
					handle_wildcards(token, num_matches, matches);
				}
				else {
					token->value = remove_quotes(token);
					k++;
				}
		}
	token = token->next;
	}
	lexerbuf->count = k;
	return k;
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
