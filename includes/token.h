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

typedef enum
{
	STRING;
	SEMI;
	LSHIFT;
	RSHIFT;
	DOUBLE_LSHIFT;
	DOUBLE_RSHIFT;
	PIPE;
	DOUBLE_QUOTE;
	QUOTE;
	LPAREN;
	RPAREN;
	AMPERSAND;
	DOLLAR;
	CURLY;
	EQUAL;
	LIMITER;
	EOF;
} token_type;

typedef struct s_token
{
	char	*value;
	enum token_type;
} t_token;

void	assign_token();
void	init_token();
#endif
