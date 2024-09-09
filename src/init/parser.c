/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:45:23 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/09 03:56:43 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"

void	init_parser(t_lexer **lex, t_syntax_tree **tree)
{
	(*tree)->branch = p_build_tree(&(*lex)->token_list);
	if ((*tree)->branch->args)
		p_expand_tree((*tree)->branch);
}
