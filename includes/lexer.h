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

typedef struct s_lexer
{
	char	c;
	char	*src;
	int		index;
	int		id;
	struct s_lexer	*lexer;	
} t_lexer;

void	init_lexer(char	*input);
//t_lexer	*lexer_next();
//t_lexer	*lexer_get_id();

#endif
