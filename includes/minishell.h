/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:59 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/04 09:32:58 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdbool.h>
# include "../lib/includes/libft.h"
# include "./structs.h"

# define MAX(a, b) a > b ? a : b

/*/////////////////////////////////////////////////////////////
////////////		INITS			    //////////
////////////////////////////////////////////////////////////*/
void	init_shell(t_env *env);
char    **copy_2d_array(char **str);
char    *fun_prompt(void);
void	clear_prompts(void);
void	l_recursive_print(t_lexer *lex, int id);

void	print_env(t_env **head);
void	split_env(char *env_str, char **key, char **value);
void	copy_env(t_env	**env_ll, char **env);


#endif
