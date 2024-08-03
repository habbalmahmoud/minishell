/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:55 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/30 12:40:57 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "./minishell.h"
# include "./token.h"

typedef struct	s_lex_utils
{
	char	c;
	int	i;
	int	j;
	char	*input;
}	t_lex_utils;

typedef struct s_lexer
{
	t_token	*token_list;
	t_lex_utils	*util;
	int		count;
} t_lexer;

/*////////////////////////////////////////
*		GLOB(3) ALT		//
*////////////////////////////////////////		
char **ft_glob(const char *pattern, int *num_matches);

/*////////////////////////////////////
///		LEX LUTHER	   //
//////////////////////////////////*/
int	init_lexer(char *input, int len, t_lexer *lex);
int	count_tokenized(t_lexer *lex, t_token **token, int type);
t_token	*init_vars(char *input, int len, t_lexer *lex, t_token *token);
void	tokenize(t_lexer *lex, t_token **token, int type, int *state);

/*////////////////////////////////////
///		LEX HELP	   //
//////////////////////////////////*/
void	clean_input(char *input, char *res);
void	handle_wildcards(t_token *token, int count, char **hits);
char	*remove_quotes(t_token *token);
int		assign_type(char c);

#endif
