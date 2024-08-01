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

# include "../../includes/lexer.h"
/* CREATE PROMPT TITLE -- display exit code, hostname and username + current working directory 
 * MISC FUNCTIONS --
 *
 * */
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
