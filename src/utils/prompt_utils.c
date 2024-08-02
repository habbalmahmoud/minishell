/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:30:08 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/02 15:48:49 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/lexer.h"
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

char    *fun_prompt(void)
{
	char *str;
	char *final;
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	str = "\033[0;36m=>  \033[0;0m";
	final = ft_strjoin(cwd, str);
	return (final);
}

void	clear_prompts(void)
{
	 printf("\033[H\033[J");
}

char    **join_2d_arrays(char **str, char **str2)
{
    char    **new;
    int     str1len;
    int     str2len;
    int     i;
    int     j;

    str1len = 0;
    if (str)
        str1len = twoD_array_length(str);
    str2len = twoD_array_length(str2);
    new = malloc (((str1len + str2len) + 1) * sizeof(char *));
    i = 0;
    j = 0;
    if (str)
    while (str[i])
        {
            new[j] = ft_strdup(str[i]);
            i++;
            j++;
        }
    i = 0;
    while (str2[i])
    {
        new[j] = ft_strdup(str2[i]);
        i++;
        j++;
    }
    new[j] = 0;
    return(new);
}

char    **ft_realloc(char **str, int count, int size)
{
    char    **new;
    int     i;
    int     str1len;

    i = 0;
    str1len = 0;
    if (str)
        str1len = twoD_array_length(str);
    new = malloc((str1len + count) * size);
    while (i < count)
    {
        new[i] = ft_calloc(1, sizeof(int));
        i++;
    }
    new [i] = 0;
    return(join_2d_arrays(str, new));
}