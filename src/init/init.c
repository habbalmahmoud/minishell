/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/30 16:29:58 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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
			printf("%s\n", lex.token_list->value);
			lex.token_list = lex.token_list->next;
		}
		free(input);
		free(prompt);
	}
}

