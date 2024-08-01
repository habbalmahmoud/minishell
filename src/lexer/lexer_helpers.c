
#include "../../includes/lexer.h"
#include "../../includes/token.h"

static int	return_whitespace(char c)
{
	if (c == ' ')
		return (SPACE);
	if (c == '\t')
		return (TAB);
	if (c == '\\')
		return (ESC);
	if (c == '\n')
		return (NEWLINE);
	if (c == '\0')
		return (FT_EOF);
}

static int	return_operators(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (LSHIFT);
	if (c == '>')
		return (RSHIFT);
	if (c == '&')
		return (AMPERSAND);
	if (c == ';')
		return (SEMI);
}

static int	return_literals(char c)
{
	if (c == 34)
		return (DOUBLE_QUOTE);
	if (c == 39)
		return (QUOTE);
	if (c == '(')
		return (LPAREN);
	if (c == ')')
		return (RPAREN);
	if (c == '=')
		return (EQUAL);
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
		return (FT_NULL);
	else
		return (WORD);
}

void	clean_input(char *input, char *res)
{
	char	end_literal;
	size_t	len;
	int	i;
	int	j;
	char c;

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


