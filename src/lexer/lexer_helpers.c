/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:45 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/02 15:55:30 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quotes(t_token *token)
{
	char*	clean;

	clean = ft_calloc(1, ft_strlen(token->value) + 1);
	clean_input(token->value, clean);
	free(token->value);
	return(clean);
}

void	handle_wildcards(t_token *token, int count, char **hits)
{
	t_token	*store;
	int		i;

	store = token->next;
        free(token->value);
        token->value = ft_calloc(1, ft_strlen(hits[0]) + 1);
        ft_strcpy(token->value, hits[0]);
	i = 1;
	while (i < count)
	{
		token->next = malloc(sizeof(t_token));
		init_token(token->next, ft_strlen(hits[i]));
		token = token->next;
		token->type = TOKEN;
		ft_strcpy(token->value, hits[i]);
		i++;
	}
	token->next = store;
	i = -1;
	while (++i < count) 
		free(hits[i]);
    	free(hits);
}

void	clean_input(char *input, char *res)
{
	char	end_literal;
	size_t	len;
	int		i;
	int		j;
	char		c;

	len = ft_strlen(input);
	end_literal = 0;
	j = 0;
	i = 0;
	if (len <= 1)
	{
		ft_strcpy(res, input);
		return ;
	}
	while (i < len)
	{
		c = input[i];
		if ((c == 34 || c == 39) && end_literal == 0)
			end_literal = 1;
		else if (end_literal == 1)
			end_literal = 0;
		else
			res[j++] = c;
		i++;
	}
	res[j] = '\0';
}

