/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:55 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/30 12:40:57 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "./minishell.h"
# include "./token.h"

typedef struct s_lexer
{
	t_token	*token_list;
	int	count;
} t_lexer;

/*////////////////////////////////////////
*		GLOB(3) ALT		//
*////////////////////////////////////////		
char **ft_glob(const char *pattern, int *num_matches);

/*////////////////////////////////////
///		LEX LUTHER	   //
//////////////////////////////////*/		
int lexer_build(char* input, int size, t_lexer *lexerbuf);
//void	init_lexer(char	*input);

/*////////////////////////////////////
///		LEX HELP	   //
//////////////////////////////////*/
int	assign_type(char c);
void	clean_input(char *input, char *res);

#endif
