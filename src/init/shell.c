/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/09 03:58:44 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/lexer.h"
#include "../../includes/ast.h"
#include "../../includes/execute.h"
#include "../../includes/signals.h"

void static	exit_helper(t_exec_utils *util)
{
	if (g_mini_code)
	{
		util->code = g_mini_code;
		g_mini_code = 0;
	}
}

void	modify_exit_code(t_env *env, t_exec_utils *util)
{
	char	*str;
	t_env	*head;
	t_env	*new;
	int		flag;

	exit_helper(util);
	head = env;
	str = ft_itoa(util->code);
	flag = 0;
	while (head)
	{
		if (!ft_strcmp(head->key, "?"))
		{
			if (head->value)
				free(head->value);
			head->value = str;
			return ;
		}
		head = head->next;
	}
	new = env_lstnew("?", str, 2);
	free(str);
	env_lstadd_back(&env, new);
}

int	init_shell(t_lexer *lex, t_exec_utils *util, t_env **env)
{
	char			*input;
	t_token			*token;
	t_syntax_tree	*tree;

	input = lex->util->input;
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		exit(util->code);
	}
	token = malloc(sizeof(t_token));
	init_lexer(input, &lex, &token, (*env));
	if (close_values(input, &lex, &util))
	{
		if (validate_lexer(&lex, &util) == 1)
		{
			tree = ft_calloc(1, sizeof(t_syntax_tree));
			init_parser(&lex, &tree);
			init_execute(tree, env, &util);
			free_ast(tree->branch);
			free(tree);
		}
	}
	modify_exit_code((*env), util);
	return (0);
}

void	prompt_loop(t_env *env)
{
	char			*input;
	t_lexer			*lex;
	t_exec_utils	*util;
	char			*code;

	util = malloc(sizeof(t_exec_utils));
	util->code = 0;
	while (1)
	{
		lex = malloc(sizeof(t_lexer));
		lex->util = malloc(sizeof(t_lex_utils));
		lex->util->rec_count = 0;
		input = readline("\033[1;3142@minishell=> \033[0;0m");
		add_history(input);
		lex->util->input = input;
		if (init_shell(lex, util, &env))
			break ;
		free(input);
		lex->util->rec_count = 0;
		free_lexer(lex);
	}
	free(util);
}
