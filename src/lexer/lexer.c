#include "../../includes/lexer.h"

void	init_lexer(char *input)
{
	int	i;

	input = ft_strtrim(input, " ");
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;

	}
}
