#include "../../includes/builtins.h"

char    *get_home_dir(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "HOME=", 5) == 0)
            return(ft_substr(env[i], 5, ft_strlen(env[i]) - 5));
        i++;
    }
}

void    handle_builtins(char *input, char **env)
{
    char    *home;
    char    *path;

    path = ft_substr(input, 3, ft_strlen(input) - 3);
    home = get_home_dir(env);
    if (ft_strncmp(input, "cd", 2) == 0)
        change_dir(path, home);
    if ((ft_strcmp(input, "pwd") == 0))
        printf("%s\n", get_dir());
    free(path);
    free(home);
}