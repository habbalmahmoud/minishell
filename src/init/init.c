/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/04 01:06:26 by mhabbal          ###   ########.fr       */
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
		handle_builtins(input, env);
		init_lexer(input, ft_strlen(input), &lex);
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

int init_lexer(char *input, int len, t_lexer *lex)
{
	int	state;
	int	type;
	t_token	*token;

	state = STATE_ANY;
	token = init_vars(input, len, lex, token);
	init_token(token, len);
	while (input[lex->util->i] != '\0') 
	{
		lex->util->c = input[lex->util->i];
		type = assign_type(lex->util->c);
		tokenize(lex, &token, type, &state);
		lex->util->i++;
	}
	if (lex->util->j > 0)
		token->value[lex->util->j] = '\0';
	token = lex->token_list;
	return (count_tokenized(lex, token, type));
}
