/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/07 16:34:26 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void    ft_print(t_lexer **lex, int lvl)
{
    t_lexer *curr = (*lex);

    while (curr->token_list)
    {
        if (!curr->sub_lex)
        {
            printf("%s\n", curr->token_list->value);
        }
        else
        {   
            printf("%s\n", curr->token_list->value);
            ft_print(&curr->sub_lex, lvl + 1);
        }
		if (curr->token_list->next)
        	curr->token_list = curr->token_list->next;
    }
}

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
		init_lexer(input, ft_strlen(input), &lex, &token);
		if (!input)
			break ;
		if (ft_strcmp(input, "clear") == 0)
			clear_prompts();
		if (ft_strcmp(input, "exit") == 0)
			exit(1);
		if (lex)
		{
			if (lex->sub_lex)
				printf("ONE1 %s\n", lex->sub_lex->token_list->value);
			if (lex->sub_lex->next)
			{

				// if (lex->sub_lex->next->token_list)
				// 	printf("TWO2\n %s\n", lex->sub_lex->next->token_list->value);
				// else
					printf("HEllo\n");	
			}
		}
		//ft_print(&lex, 0);
		free(input);
		lex->util->rec_count = 0;
		lex->util->clock = 0;
	}
}

int init_lexer(char *input, int len, t_lexer **lex, t_token **token)
{
	int	state;
	int	type;

	state = STATE_ANY;
	(*token) = init_vars(input, len, (*lex), (*token));
	init_token((*token), len);
	while (*(*lex)->util->c_input) 
	{
		(*lex)->util->c = *(*lex)->util->c_input;
		type = assign_type((*lex)->util->c);
		if (tokenize((*lex), token, type, &state) == 1)
			return (count_tokenized((*lex), (*token), type));
		(*lex)->util->i++;
		(*lex)->util->c_input++;
	}
	if ((*lex)->util->j > 0)
		(*token)->value[(*lex)->util->j] = '\0';
	(*token) = (*lex)->token_list;
	return (count_tokenized((*lex), (*token), type));
}
