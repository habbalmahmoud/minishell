/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:28:07 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/30 12:28:09 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "./minishell.h"


// /*
//                  __ PIPE__
//                      ___/              \____
//                     /                       \
//             COMMAND                    __ PIPE _
//           /        \                  /         \
//     ARGUMENTS   REDIRECTIONS	    CMD        _ CMD__
//         |          |     |           |           /    \
//        cat        <<     >       ARGUMENTS    ARGUMENTS	    REDIR
//                    |     |         |   |      |   |   |        |
//                  "..."  file      wc  -c      tr  -d " "       >
//                                                                |
//                                                              file2
// */

typedef enum
{
	TYPE_SPACE = 32,
	TYPE_WORD = -42,
	TYPE_SEMI = ';',
	TYPE_LSHIFT = '<',
	TYPE_RSHIFT = '>',
	TYPE_PIPE = '|',
	TYPE_DOUBLE_QUOTE = 34,
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
} token_type;

typedef enum
{
	INSIDE_QUOTES,
	INSIDE_DQUOTES,
	INSIDE_ESC,
	ANY,
	
} token_state;

typedef struct s_token
{
	char	*value;
	int	type;
	struct s_token *next;
} t_token;

void	free_token(t_token *token);
void	init_token(t_token *token, int n);

#endif
