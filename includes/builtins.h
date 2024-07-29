#ifndef BUILTINS_H
# define BUILTINS_H
# include "./minishell.h"


char	*get_dir(void);
char	*get_env(void);
void	change_dir(const char *path);

#endif

