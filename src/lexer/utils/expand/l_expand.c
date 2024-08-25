#include "../../../../includes/minishell.h"
#include "../../../../includes/lexer.h"
#include "../../../../includes/token.h"


char	*l_expand(char *str, t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (!(ft_strcmp(str, head->key)))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}


void	l_handler_expand(t_token *token, char *expanded)
{
	(void)token;
	printf("%s", expanded);
}
