/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:45:23 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/09 14:46:27 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"
#include "../../includes/minishell.h"

// void	free_token_llist(t_token **token_list)
// {
// 	t_token	*current;
// 	t_token	*next;

// 	current = (*token_list);
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		if (current->value)
// 			free(current->value);
// 		if (current->sub_lexer)
// 			free_lexer(current->sub_lexer);
// 		free(current);
// 		current = next;
// 	}
// }

void	init_parser(t_lexer **lex, t_syntax_tree **tree)
{
	(*tree)->branch = p_build_tree(lex);
	if ((*tree)->branch->args)
		p_expand_tree((*tree)->branch);
}
