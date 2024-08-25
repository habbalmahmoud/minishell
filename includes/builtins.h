/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:41:09 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/30 12:41:09 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "./minishell.h"

// IF ANY ENV GETS UNSET OR IS NULL DO CHECKS IN BUILTIN COMMANDS TO RETURN ERRROS (SEE BASH)
// EXAMPLES: UNSET OLDPWD -> CD - SHOULD RETURN AN ERROR CHECK IF OLDPWD IS NULL WHEN CHDIRing INTO IT
// EXAMPLES: UNSETTING HOME ENV AND CD INTO HOME SHOULD NOT RETURN AND ERROR BUT TAKE YOU BACK TO THE ROOT DIR (CHECK BASH FOR CONFIRMATION)
// CHECK FOR OTHER ODD BEHAVOIRS IN BASH.
// CAT | CAT | ls -> fully functional now.

char	*get_dir(void);
char	*get_env(void);
void	change_dir(const char *path, char *home);
void    handle_builtins(char *input, char **env);

#endif

