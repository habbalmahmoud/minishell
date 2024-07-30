#include "../../includes/minishell.h"

void	init_shell(char **env)
{
	char	*input;

	while (1)
	{
		input = readline("death> ");
		if (!input)
			break ;	
		add_history(input);
		init_lexer(input);
		free(input);
	}
}
