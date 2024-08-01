
# include "../../includes/lexer.h"
# include "../../includes/token.h"

void	init_token(t_token *token, int n)
{
	token->value = ft_calloc(1, n + 1);
	token->value[0] = 0;
	token->type = FT_NULL;
	token->next = NULL;
}


void	free_token(t_token *token)
{
	if (token)
	{
		free(token->value);
		free_token(token->next);
		free(token);
	}
}

