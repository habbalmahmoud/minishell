#include "../../includes/minishell.h"

void	change_dir(const char *path) 
{
	if (path == NULL || path[0] == '\0')
	{
		printf("cd: missing argument\n");
		return ;
	}

	if (chdir(path) != 0)
		perror("cd");
}
