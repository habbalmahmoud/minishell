
/* CREATE PROMPT TITLE -- display exit code, hostname and username + current working directory 
 * MISC FUNCTIONS --
 *
 * */

#include "../../includes/minishell.h"

int twoD_array_length(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char    **copy_2d_array(char **str)
{
    int     big_len;
    char    **copy_str;
    int     i;

    i = 0;
    big_len = twoD_array_length(str);
    copy_str = malloc((big_len + 1) * sizeof(char *));
    while (str[i])
    {
        copy_str[i] = ft_strdup(str[i]);
        i++;
    }
    copy_str[i] = NULL;
    return (copy_str);
}