/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:33:24 by mhabbal           #+#    #+#             */
/*   Updated: 2024/09/09 15:08:02 by nkanaan          ###   ########.fr       */
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

void free_token_list(t_token *token_list) {
    t_token *temp;

    while (token_list) {
        temp = token_list;
        if (token_list->sub_lexer) {
            // Free sub-lexer's token list and itself
            free_token_list(token_list->sub_lexer->token_list);
            free(token_list->sub_lexer->util); // Free the utility structure
            free(token_list->sub_lexer);       // Free the sub-lexer itself
        }
        token_list = token_list->next;
        free(temp->value); // Assuming value is dynamically allocated
        free(temp);        // Free the current token
    }
}

void free_lexer(t_lexer *lexer) {
    if (!lexer) return;
    
    // Free the token list
    free_token_list(lexer->token_list);
    
    // Free the c_token if needed
    if (lexer->c_token) {
        free(lexer->c_token->value); // Assuming value is dynamically allocated
        free(lexer->c_token);
    }
    
    // Free the utility structure
    if (lexer->util) {
        free(lexer->util);
    }
    
    // Free the lexer itself
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
