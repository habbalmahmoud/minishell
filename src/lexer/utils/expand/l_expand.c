#include "../../../../includes/minishell.h"
#include "../../../../includes/lexer.h"
#include "../../../../includes/token.h"


char	*l_expand(char *str, t_env *env)
{
	t_env	*head;
	char	*delim;

	head = env;
	delim = ft_strchr(str, '$');
	while (head)
	{
		if (delim)
		{
			if (!(ft_strcmp(delim + 1, head->key)))
				return (head->value);
		}
		head = head->next;
	}
	return (NULL);
}

void	l_handler_expand(t_token *token, char *expanded)
{
	free(token->value);
	size_t len = ft_strlen(expanded);
	token->value = ft_calloc(len, sizeof(char) + 1);
	ft_strcpy(token->value, expanded);
}

