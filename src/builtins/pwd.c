#include "../../includes/minishell.h"

char	*get_dir(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL) 
	{
		perror("getcwd() error");
		exit(1);
	}
	return (cwd);
}
