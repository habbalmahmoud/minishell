/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/15 18:24:05 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/lexer.h"
#include "../../includes/ast.h"
#include "../../includes/execute.h"

void	init_shell(char **env)
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
	(void)env;
	while (1)
	{
		input = readline("\033[1;31mnkanaan@minishell=> \033[0;0m");
		add_history(input);
		//handle_builtins(input, env);
		init_lexer(input, 0, &lex, &token);
		init_parser(&lex, &tree);
		//init_execute(tree, env);
		if (!input)
			break ;
		if (ft_strcmp(input, "clear") == 0)
			clear_prompts();
		if (ft_strcmp(input, "exit") == 0)
			exit(1);
		free(input);
		lex->util->clock = 0;
		lex->util->rec_count = 0;
	}
}
