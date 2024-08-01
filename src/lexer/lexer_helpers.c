/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:45 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/01 15:42:47 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/lexer.h"
#include "../../includes/token.h"

static int	return_whitespace(char c)
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

static int	return_operators(char c)
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

static int	return_literals(char c)
{
	if (c == 34)
		return (TYPE_DOUBLE_QUOTE);
	if (c == 39)
		return (TYPE_QUOTE);
	if (c == '(')
		return (TYPE_LPAREN);
	if (c == ')')
		return (TYPE_RPAREN);
	if (c == '=')
		return (TYPE_EQUAL);
}

int	assign_type(char c)
{
	if (c == ' ' || c == '\t' || c == '\\' || c == '\n')
		return (return_whitespace(c));
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == ';')
		return (return_operators(c));
	if (c == 34 || c == 39 || c == '(' || c == ')' || c == '=')
		return (return_literals(c));
	if (c == 0)
		return (TYPE_NULL);
	else
		return (TYPE_WORD);
}

void	clean_input(char *input, char *res)
{
	char	end_literal;
	size_t	len;
	int		i;
	int		j;
	char		c;

	len = ft_strlen(input);
	end_literal = 0;
	j = 0;
	i = 0;
	if (len <= 1)
	{
		ft_strcpy(res, input);
		return ;
	}
	while (i < len)
	{
		c = input[i];
		if ((c == 34 || c == 39) && end_literal == 0)
			end_literal = c;
		else if (end_literal == c)
			end_literal = 0;
		else
			res[j++] = c;
		i++;
	}
	res[j] = '\0';
}


