/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:59 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/02 14:52:40 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "../lib/includes/libft.h"
# include "./token.h"
# include "./lexer.h"
# include "./builtins.h"

# define MAX(a, b) a > b ? a : b

void	init_shell(char **env);
char    **copy_2d_array(char **str);
int     twoD_array_length(char **str);
char    *fun_prompt(void);
void	clear_prompts(void);
char    **ft_realloc(char **str, int count, int size);


/*////////////////////////////////////////
//////          BUILTINS            //////
///////////////////////////////////////*/
char    *get_dir(void);


#endif
