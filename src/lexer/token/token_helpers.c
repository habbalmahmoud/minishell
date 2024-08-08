/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:57:01 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/08 14:03:21 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"
#include "../../../includes/token.h"
#include "../../../includes/lexer.h"

int	return_whitespaces(char c)
{
	if (c == ' ')
		return (TYPE_SPACE);
	if (c == '\t')
		return (TYPE_TAB);
	if (c == '\\')
		return (TYPE_ESC);
	if (c == '\n')
		return (TYPE_NEWLINE);
	if (c == '\0')
		return (TYPE_EOF);
}

int	return_operators(char c)
{
	if (c == '|')
		return (TYPE_PIPE);
	if (c == '<')
		return (TYPE_LSHIFT);
	if (c == '>')
		return (TYPE_RSHIFT);
	if (c == '&')
		return (TYPE_AMPERSAND);
	if (c == ';')
		return (TYPE_SEMI);
}

int	return_literals(char c)
{
	if (c == 34)
		return (TYPE_DQUOTE);
	if (c == 39)
		return (TYPE_QUOTE);
	if (c == '(')
		return (TYPE_LPAREN);
	if (c == ')')
		return (TYPE_RPAREN);
	if (c == '=')
		return (TYPE_EQUAL);
}
