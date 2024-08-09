/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/09 09:31:57 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include "../../includes/lexer.h"


static t_token	*init_shell_vars(t_lexer *lex);

void	init_shell(char **env)
{
	char	*input;
	t_lexer	*lex;
	t_token	*token;

	lex = NULL;
	token = init_shell_vars(lex);
	while (1)
	{
		input = readline("\033[1;31m=> \033[0;0m");
		add_history(input);
		handle_builtins(input, env);
		init_lexer(input, 0, &lex, &token);
		if (!input)
			break ;
		if (ft_strcmp(input, "clear") == 0)
			clear_prompts();
		if (ft_strcmp(input, "exit") == 0)
			exit(1);
		l_recursive_print(lex, 0);
		free(input);
		lex->util->clock = 0;
		lex->util->rec_count = 0;
	}
}

static t_token	*init_shell_vars(t_lexer *lex)
{
	t_token *token;

	lex = malloc(sizeof(t_lexer));
	lex->util = malloc(sizeof(t_lex_utils));
	lex->util->rec_count = 0;
	token = malloc(sizeof(t_token));
	return (token);
}
