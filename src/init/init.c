/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/08 16:55:34 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/token.h"
#include "../../includes/lexer.h"
void	init_shell(char **env)
{
	char	*input;
	t_lexer	*lex;
	t_token	*token;
	char 	user[1024];
	char 	host[1024];

	getlogin_r(user, sizeof(user));
	gethostname(host, sizeof(host));
	lex = malloc(sizeof(t_lexer));
	lex->util = malloc(sizeof(t_lex_utils));
	lex->util->rec_count = 0;
	token = malloc(sizeof(t_token));
	while (1)
	{
		printf("~%s@%s ", user, host);
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
		// while (lex->token_list)
		// {
		// 	printf("MAIN: %s\n", lex->token_list->value);
		// 	if (ft_strcmp("(", lex->token_list->value) == 0)
		// 	{
		// 		while ((*lex->child)->id != lex->token_list->id)
		// 			*lex->child = (*lex->child)->next;
		// 		while ((*lex->child)->lexer->token_list)
		// 		{
		// 			printf("SUB: %s\n", (*lex->child)->lexer->token_list->value);
		// 			if (!(ft_strcmp("()", (*lex->child)->lexer->token_list->value)))
		// 			{
		// 				while ((*(*lex->child)->lexer->child)->id != (*lex->child)->lexer->token_list->id)
		// 					(*(*lex->child)->lexer->child) = (*(*lex->child)->lexer->child)->next;
		// 				while ((*lex->child)->lexer->token_list)
		// 				{
		// 					printf("SUB SUB: %s\n", (*lex->child)->next->lexer->token_list->value);
		// 					(*(*lex->child)->lexer->child) = (*(*lex->child)->lexer->child)->next;
		// 				}
		// 			}
		// 			(*lex->child)->lexer->token_list = (*lex->child)->lexer->token_list->next;
		// 		}
		// 	}
		// 	lex->token_list = lex->token_list->next;
		// }
		printf("MAIN: %s\n", (*lex->child)->lexer->token_list->value);
		// // if ((*(*(*lex->child)->lexer->child)->lexer->child))
		// printf("%s\n", (*(*lex->child)->lexer->child)->lexer->token_list->next->value);
		free(input);
		lex->util->rec_count = 0;
		lex->util->clock = 0;
	}
}

int init_lexer(char *input, int id, t_lexer **lex, t_token **token)
{
	int	state;
	int	type;
	size_t len;

	len = ft_strlen(input);
	state = STATE_ANY;
	(*token) = init_vars(input, len, (*lex), (*token));
	init_token((*token), len, id);
	while (*(*lex)->util->c_input) 
	{
		(*lex)->util->c = *(*lex)->util->c_input;
		type = assign_type((*lex)->util->c);
		// printf("INIT: %c  ", (*(*lex)->util->c_input));
		// printf("\n");
		if (tokenize((*lex), token, type, &state) == 1)
		{
			if ((*lex)->util->j > 0)
				(*token)->value[(*lex)->util->j] = '\0';
			return (count_tokenized((*lex), (*token), type));
		}
		(*lex)->util->i++;
		(*lex)->util->c_input++;
	}
	if ((*lex)->util->j > 0)
		(*token)->value[(*lex)->util->j] = '\0';
	(*token) = (*lex)->token_list;
	return (count_tokenized((*lex), (*token), type));
}
