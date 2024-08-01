/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:59 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/30 16:30:42 by nkanaan          ###   ########.fr       */
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

# define MAX(a, b) a > b ? a : b

void	init_shell(char **env);
char    *fun_prompt(void);
void	clear_prompts(void);



/*////////////////////////////////////////
//////          BUILTINS            //////
///////////////////////////////////////*/
char    *get_dir(void);


#endif
