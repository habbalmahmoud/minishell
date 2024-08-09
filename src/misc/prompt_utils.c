/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:30:08 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/30 16:30:09 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

