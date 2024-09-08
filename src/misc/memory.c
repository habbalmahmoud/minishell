/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:33:24 by mhabbal           #+#    #+#             */
/*   Updated: 2024/09/08 18:24:19 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/token.h"
#include "../../includes/ast.h"

static void	free_tree(t_syntax_tree *tree)
{
	if (tree->branch)
		free_ast(tree->branch);
}

void	free_ast(t_ast_node *node)
{
	if (node)
	{
		if (node->tree_link)
		{
			free_tree(node->tree_link);
			free(node->tree_link);
		}
		if (node->left)
			free_ast(node->left);
		if (node->right)
			free_ast(node->right);
		if (node->args)
			free_split(node->args);
		if (node->in)
			free(node->in);
		if (node->out)
			free(node->out);
		free(node);
	}
}

void	free_token_list(t_token *token_list)
{
	t_token	*current;
	t_token	*next;

	current = token_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		if (current->sub_lexer)
			free_lexer(current->sub_lexer);
		free(current);
		current = next;
	}
}

void	free_lexer(t_lexer *lexer)
{
	if (!lexer)
		return ;
	free_token_list(lexer->token_list);
	free(lexer->util);
	free(lexer);
}

void	free_env_list(t_env **env)
{
	t_env	*curr;
	t_env	*next;

	curr = (*env);
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
}
