/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:07:38 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/28 15:30:17 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"
#include "../../../includes/execute.h"

int	l_token_count(t_lexer *lex, t_token *token, t_env *env)
{
	int	hits;
	char	**matches;
	char	**expanded;
	char	*exp = NULL;
	char	**spp;
	
	token = lex->token_list;
	expanded = NULL;
	spp = NULL;
	while (token)
	{
		if (token->type == TOKEN)
		{
			matches = l_glob(token->value, &hits);
			if (hits > 0)
				l_handler_wildcards(token, hits, matches);			
			else
				token->value = l_remove_quotes(token);
			if (ft_strchr(token->value, '$') != NULL)
				spp = ft_split(ft_strchr(token->value, '$'), ' ');
			if (spp && spp[0])
				if (lex->util->expand && ft_strlen(spp[0]) == 1)
					lex->util->expand = 0;
			if (ft_strchr(token->value, '$') && lex->util->expand)
			{
				char	**test;
				int flag = 0;
				if (token->value[0] != '$')
					flag = 1;
				test = ft_split(token->value, '$');
				int	i = 0;
				if (test)
				{
					while (test[i])
				{
					if (test[i][0] == '?')
						flag = 2;	
					expanded = l_expand(test[i], env, flag);
					if (expanded)
					{
						if (i == 0)
						{
							free(token->value);
							token->value = ft_strdup("");
						}
						if (flag)
							{
								token->value = ft_strjoin(token->value, expanded[0]);
								flag = 0;	
							}
							else
						{
								exp = l_handler_expand(test[i], expanded);
							token->value = ft_strjoin(token->value, exp);

							}
					}
					else if (ft_strchr(token->value, '$') && lex->util->expand)
					{
						free(token->value);
						token->value = ft_strdup("");
					}
					i++;
				}

				}
			}
			
		}
		token = token->next;
	}
	return (0);
}

void	l_tokenize_words(t_lexer *lex, t_token *token, int type)
{
	if (type == TYPE_ESC)
	{
		token->value[lex->util->j++] = ++(*lex->util->input_ptr);
		token->type = TOKEN;
	}
	else if (type == TYPE_WORD)
	{
		token->value[lex->util->j++] = lex->util->c;
		token->type = TOKEN;
	}
}

void	l_tokenize_next(t_lexer *lex, t_token **token, int type, int len)
{
	if (lex->util->j > 0)
	{
		(*token)->value[lex->util->j] = '\0';
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
	}
	if (type != TYPE_SPACE)
	{
		(*token)->value[0] = type;
		(*token)->value[1] = '\0';
		(*token)->type = type;
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
	}
}
