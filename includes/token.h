/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:28:07 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/08 13:25:10 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "./minishell.h"
// # include "../lib/includes/list.h"


struct	s_lex_utils;
struct s_lexer;
struct s_list;
struct s_token;



typedef enum e_token_type
{
	TYPE_SPACE = 32,
	TYPE_WORD = -42,
	TYPE_SEMI = ';',
	TYPE_LSHIFT = '<',
	TYPE_RSHIFT = '>',
	TYPE_PIPE = '|',
	TYPE_DQUOTE = 34,
	TYPE_QUOTE = 39,
	TYPE_LPAREN = '(',
	TYPE_RPAREN = ')',
	TYPE_AMPERSAND = '&',
	TYPE_DOLLAR = '$',
	TYPE_EQUAL = '=',
	TYPE_TAB = '\t',
	TYPE_NEWLINE = '\n',
	TYPE_ESC = '\\',
	TYPE_EOF = '\0',
	TYPE_NULL = 0,
	TOKEN = -42,
	IN_QUOTES,
	IN_DQUOTES,
	IN_ESC,
	STATE_ANY,
	IN_AND,
	IN_OR,
	IN_PARAN,
}	t_token_type;


typedef struct s_token
{
	char	*value;
	int		type;
	struct s_token *next;
	int		id;
} t_token;

typedef struct	s_lex_utils
{
	char	c;
	int	i;
	int	j;
	char	*input;
	char	*c_input;
	int		glob_c;
	int		rec_count;
	int		clock;
}	t_lex_utils;

typedef struct s_list
{
	int				id;
	struct s_list		*next;
	struct s_lexer				*lexer;
}	t_list;

typedef struct s_lexer
{
	t_token	*token_list;
	t_lex_utils	*util;
	t_list		**child;
	int		count;
} t_lexer;



int	return_whitespaces(char c);
int	return_operators(char c);
int	return_literals(char c);
void	free_token(t_token *token);
void	init_token(t_token *token, int n, int id);

#endif
