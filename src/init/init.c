/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/05 17:00:13 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_shell(char **env)
{
	char	*input;
	t_lexer	lex;
	t_token	*token;
	char 	user[1024];
	char 	host[1024];

	getlogin_r(user, sizeof(user));
	gethostname(host, sizeof(host));
	lex.util = malloc(sizeof(t_lex_utils));
	lex.util->rec_count = 0;
	token = malloc(sizeof(t_token));
	while (1)
	{
		printf("~%s@%s ", user, host);
		input = readline("\033[1;31m=> \033[0;0m");
		add_history(input);
		handle_builtins(input, env);
		init_lexer(input, ft_strlen(input), &lex, &token);
		if (!input)
			break ;
		if (ft_strcmp(input, "clear") == 0)
			clear_prompts();
		if (ft_strcmp(input, "exit") == 0)
			exit(1);
		while (lex.token_list)
		{
				printf("%s\n", lex.token_list->sub_token->sub_token->value);
			lex.token_list = lex.token_list->next;
		}
		free(input);
	}
}

int init_lexer(char *input, int len, t_lexer *lex, t_token **token)
{
	int	state;
	int	type;

	state = STATE_ANY;
	(*token) = init_vars(input, len, lex, (*token));
	init_token((*token), len);
		// printf("I am here\n");
	while (*lex->util->c_input) 
	{
		// printf("%c\n", *lex->util->c_input);
		lex->util->c = *lex->util->c_input;
		type = assign_type(lex->util->c);
		
		if (tokenize(lex, token, type, &state) == 1)
			return (count_tokenized(lex, (*token), type));
		lex->util->i++;
		lex->util->c_input++;
	}
	if (lex->util->j > 0)
		(*token)->value[lex->util->j] = '\0';
	(*token) = lex->token_list;
	return (count_tokenized(lex, (*token), type));
}
