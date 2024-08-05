/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:45 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/04 03:05:48 by mhabbal          ###   ########.fr       */
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

void	handle_wildcards(t_token *token, int count, char **glob_list)
{
	t_token	*store;
	int	i = 0;

	store = token->next;
	free(token->value);
	token->value = ft_calloc(1, ft_strlen(glob_list[0]) + 1);
	ft_strcpy(token->value, glob_list[0]);
	while (++i < count)
	{
		token->next = ft_calloc(1, sizeof(t_token));
		init_token(token->next, ft_strlen(glob_list[i]));
		token = token->next;
		token->type = TOKEN;
		ft_strcpy(token->value, glob_list[i]);
	}
	token->next = store;
	// ft_lstclear(c_glob_list);
}

void	handle_wildcards_2(t_token *token, char *match, int *clock)
{
	t_token *store;
	int		i;
	
	i = 0;
	if (ft_strncmp(token->value, "*", 1) == 0)
	{
		store = token->next;
		free(token->value);
		token->value = ft_calloc(1, ft_strlen(match) + 1);
		ft_strcpy(token->value, match);
		*clock += 1;
	}
	else
	{
		// store = token->next;
		// token = token->next;
		if (!token->next)
		{
			token->next = ft_calloc(1, sizeof(t_token));
			init_token(token->next, ft_strlen(match) + 1);
			token = token->next;
			token->type = TOKEN;
			store = NULL;
		}
		// else
		// {
		// 	while (i < *clock)
		// 	{
		// 		token = token->next;
		// 		i++;
		// 	}
		// 	store = token;
		// 	*clock += 1;
		// 	free(token->value);
		// 	token->value = ft_calloc(1, ft_strlen(match) + 1);
		// }
		// ft_strcpy(token->value, match);
	}
	token->next = store;
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

int	count_tokenized(t_lexer *lex, t_token *token, int type)
{
	int	count;
	int	hits;
	t_list	*glob_list;
	t_token *temp;
	int		clock;
	
	clock = 0;
	count = 0;
	glob_list = NULL;
	token = lex->token_list;
	temp = token;
	while (token)
	{
		if (token->type == TOKEN)
		{
			hits = ft_glob(token->value, &glob_list);
			// printf("%d\n", hits);
			if (hits > 0)
			{
				count += hits;
				int	i = 0;
				char **matches = ft_calloc(hits, sizeof(char *));
				while (i < hits && glob_list)
				{
					matches[i] = ft_strdup(glob_list->content);
					printf("%s\n", matches[i]);
					glob_list = glob_list->next;
					i++;
				}
				// i = 0;
				// while (matches[i])
				// {
				// 	printf("%s\n", matches[i]);
				// 	i++;
				// }
				// printf("%s\n", token->next->value);
				// while (glob_list)
				// {
				// 	handle_wildcards_2(token, glob_list->content, &clock);
				// 	glob_list = glob_list->next;
				// }
				handle_wildcards(token, count, matches);
			}
			else
			{
				token->value = remove_quotes(token);
				count++;
			}
		}
		token = token->next;
	}
	lex->count = count;
	return (count);
}
