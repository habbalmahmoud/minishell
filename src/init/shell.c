/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/22 12:15:26 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/lexer.h"
#include "../../includes/ast.h"
#include "../../includes/execute.h"

void	print_lex(t_lexer **lexer, int id)
{
	if (!(*lexer))
		return ;
	while ((*lexer)->token_list)
	{
		if (id == 0)
			printf("Main level %d: %s\n", id, (*lexer)->token_list->value);
		else
			printf("Sub level %d: %s\n", id, (*lexer)->token_list->value);
		if ((*lexer)->token_list->sub_lexer)
			print_lex(&(*lexer)->token_list->sub_lexer, id + 1);
		(*lexer)->token_list = (*lexer)->token_list->next;
	}
}


void	init_shell(t_env *env)
{
	char	*input;
	t_lexer	*lex;
	t_token	*token;
	t_syntax_tree *tree;

	tree = malloc(sizeof(t_syntax_tree));
	lex = malloc(sizeof(t_lexer));
	lex->util = malloc(sizeof(t_lex_utils));
	lex->util->rec_count = 0;
	token = malloc(sizeof(t_token));
	while (1)
	{
		input = readline("\033[1;31mnkanaan@minishell=> \033[0;0m");
		add_history(input);
		//handle_builtins(input, env);
		init_lexer(input, &lex, &token, env);
		close_values(input, &lex);
		//print_lex(&lex, 0);
		init_parser(&lex, &tree);
		init_execute(tree, env);
		free(input);
		lex->util->clock = 0;
		lex->util->rec_count = 0;
	}
}
