/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:55 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/05 16:56:15 by mhabbal          ###   ########.fr       */
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
	char	*c_input;
	int		glob_c;
	int		rec_count;
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
char	**ft_glob(const char *pattern, int *hits);

/*////////////////////////////////////
///		LEX LUTHER	   //
//////////////////////////////////*/
int	init_lexer(char *input, int len, t_lexer *lex, t_token **token);
int	count_tokenized(t_lexer *lex, t_token *token, int type);
t_token	*init_vars(char *input, int len, t_lexer *lex, t_token *token);
int		tokenize(t_lexer *lex, t_token **token, int type, int *state);
void	handle_and_state(t_lexer *lex, t_token **token, int type, int len);
void	handle_or_state(t_lexer *lex, t_token **token, int type, int len);
void	lex_and(t_lexer *lex, t_token **token, int *state, int type);
void	lex_or(t_lexer *lex, t_token **token, int *state, int type);

/*////////////////////////////////////
///		LEX HELP	   //
//////////////////////////////////*/
void	clean_input(char *input, char *res);
void	handle_wildcards(t_token *token, int count, char **matches);
void	handle_wildcards_2(t_token *token, char *match, int *clock);
char	*remove_quotes(t_token *token);
int		assign_type(char c);
int		handle_paran(t_lexer *lex, t_token **token, int *state, int type);

#endif
