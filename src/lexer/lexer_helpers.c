/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:45 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/01 15:42:47 by nkanaan          ###   ########.fr       */
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
	printf("%s\n", input);
	while (i < len)
	{
		c = input[i];
		if ((c == 34 || c == 39) && end_literal == 0)
			end_literal = c;
		else if (end_literal == c)
			end_literal = 0;
		else
			res[j++] = c;
		i++;
	}
	res[j] = '\0';
}

t_token	*init_vars(char *input, int len, t_lexer *lex, t_token *token)
{
	lex->token_list = malloc(sizeof(t_token));
	token = lex->token_list;
	lex->util = malloc(sizeof(t_lex_utils));
	lex->util->i = 0;
	lex->util->j = 0;
	lex->util->input = input;
	return (token);
}

int	count_tokenized(t_lexer *lex, t_token **token, int type)
{
	int	count;
	char	**matches;
	int	hits;
	
	count = 0;
	while ((*token))
	{
		if ((*token)->type == TOKEN)
		{
			matches = ft_glob((*token)->value, &hits);
			if (hits > 0)
			{
				count += hits;
				handle_wildcards((*token), hits, matches);
			}
			else
			{
				(*token)->value = remove_quotes((*token));
				count++;
			}
		}
		(*token) = (*token)->next;
	}
	lex->count = count;
	return (count);
}
