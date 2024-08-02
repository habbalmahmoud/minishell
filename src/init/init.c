/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/02 14:22:23 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_shell(char **env)
{
	char	*input;
	t_lexer	lex;
	char 	user[1024];
	char 	host[1024];

	getlogin_r(user, sizeof(user));
	gethostname(host, sizeof(host));
	while (1)
	{
		printf("~%s@%s ", user, host);
		input = readline("\033[1;31m=> \033[0;0m");
		add_history(input);

		init_lexer(input, ft_strlen(input), &lex);
		handle_builtins(input, env);

		if (!input)
			break ;
		if (ft_strcmp(input, "clear") == 0)
			clear_prompts();
		if (ft_strcmp(input, "exit") == 0)
			exit(1);
		
		while (lex.token_list)
		{
			printf("%s\n", lex.token_list->value);
			lex.token_list = lex.token_list->next;
		}
		free(input);
	}
}

/*
void	init_shell(char **env)
{
	char	*input;
	t_lexer	lex;
	char	*prompt;
	char 	user[1024];
	char 	host[1024];

	while (1)
	{
		input = readline("minishell >");
		add_history(input);
		init_lexer(input, ft_strlen(input), &lex);
		while (lex.token_list)
		{
			printf("VALUE: %s\n", lex.token_list->value);
			lex.token_list = lex.token_list->next;
		}
		free(input);
	}
} */

