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

void print_lex(t_lexer **lexer)
{
	printf("%s\n", (*lexer)->token_list->next->value);
}

void	init_shell(char **env)
{
	char	*input;
	t_lexer	*lex;
	t_token	*token;
	t_syntax_tree *tree;

	(void)env;
	tree = malloc(sizeof(t_syntax_tree));
	lex = malloc(sizeof(t_lexer));
	lex->util = malloc(sizeof(t_lex_utils));
	lex->util->rec_count = 0;
	token = malloc(sizeof(t_token));
	(void)tree;
	// while (1)
	// {
		// input = readline("\033[1;31mnkanaan@minishell=> \033[0;0m");
		input = "(cmd1 file && cmd2 file2) && hello";
		add_history(input);
		// rl_replace_line("hello", 0);
		//handle_builtins(input, env);
		init_lexer(input, 0, &lex, &token);
		// print_lex(&lex);
		init_parser(&lex, &tree);
		// l_recursive_print(lex, 0);
		// if (!input)
		// 	break ;
		if (ft_strcmp(input, "clear") == 0)
			clear_prompts();
		if (ft_strcmp(input, "exit") == 0)
			exit(1);
		// free(input);
		lex->util->clock = 0;
		lex->util->rec_count = 0;
	// }
}

/*
static t_token	*init_shell_vars(t_lexer *lex)
{
	t_token *token;

	lex = malloc(sizeof(t_lexer));
	lex->util = malloc(sizeof(t_lex_utils));
	lex->util->rec_count = 0;
	token = malloc(sizeof(t_token));
	return (token);
} */
