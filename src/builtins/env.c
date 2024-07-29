#include "../../includes/minishell.h"

char	*get_env(void)
{
	char *env;

	env = getenv(0);
	if (env == NULL) 
	{
		perror("getenv() error");
		exit(1);
	}
	return (env);
}
