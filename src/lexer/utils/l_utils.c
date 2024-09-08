/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:07:38 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/08 18:24:53 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"
#include "../../../includes/execute.h"

int	l_token_count(t_lexer *lex, t_token *token, t_env *env)
{
	int		hits;
	char	**matches;
	char	*expanded;

	token = lex->token_list;
	while (token)
	{
		if (token->type == TOKEN)
		{
			matches = l_glob(token->value, &hits);
			if (hits > 0)
				l_handler_wildcards(token, hits, matches);
			else
				token->value = l_remove_quotes(token);
			expanded = expand_variables(token->value, token->expand, env);
			if (expanded)
			{
				free(token->value);
				token->value = expanded;
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
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
	}
}

int	validate_lexer(t_lexer **lex, t_exec_utils **utils)
{
	t_token	*temp;

	temp = (*lex)->token_list;
	if (!ft_strcmp(temp->value, "|") || !ft_strcmp(temp->value, "||")
		|| !ft_strcmp(temp->value, "&&") || !ft_strcmp(temp->value, ">>")
		|| !ft_strcmp(temp->value, ">") || !ft_strcmp(temp->value, ";"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" `", 2);
		ft_putstr_fd(temp->value, 2);
		ft_putendl_fd("\'", 2);
		(*utils)->code = 2;
		return (0);
	}
	if (!ft_strcmp(temp->value, "<") || !ft_strcmp(temp->value, "<<"))
	{
		if (!temp->next || temp->next->type != TYPE_WORD)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token", 2);
			ft_putstr_fd(" `", 2);
			ft_putstr_fd(temp->value, 2);
			ft_putendl_fd("\'", 2);
			(*utils)->code = 2;
			return (0);
		}
	}
	while (temp)
	{
		if (temp->type == TYPE_LPAREN)
		{
			if (!temp->sub_lexer || !temp->sub_lexer->token_list->value[0])
			{

				ft_putstr_fd("minishell: syntax error near unexpected token", 2);
				ft_putstr_fd(" `", 2);
				ft_putstr_fd(temp->value, 2);
				ft_putendl_fd("\'", 2);
				(*utils)->code = 2;
				return (0);	
			}
			if (!validate_lexer(&temp->sub_lexer, utils))
				return (0);
		}
		if (temp->next)
		{
			if (!ft_strcmp(temp->next->value, ";"))
			{
				if (temp->type != TYPE_WORD)
				{

					ft_putstr_fd("minishell: syntax error near unexpected token", 2);
					ft_putstr_fd(" `", 2);
					ft_putstr_fd(temp->value, 2);
					ft_putendl_fd("\'", 2);
					(*utils)->code = 2;
					return (0);
				}
			}
			if (temp->next->type == TYPE_PIPE || !ft_strcmp(temp->next->value, "||")
				|| !ft_strcmp(temp->next->value, "&&") || !ft_strcmp(temp->next->value, ">>")
				|| !ft_strcmp(temp->next->value, ">") || !ft_strcmp(temp->next->value, "<")
				|| !ft_strcmp(temp->next->value, "<<"))
			{
				if (!temp->next->next)
				{
					ft_putstr_fd("minishell: syntax error near unexpected token", 2);
					ft_putstr_fd(" `", 2);
					ft_putstr_fd(temp->value, 2);
					ft_putendl_fd("\'", 2);
					(*utils)->code = 2;
					return (0);
				}
				if (temp->next->type == TYPE_PIPE)
				{
					if (temp->type != TYPE_WORD && (temp->next->next->type != TYPE_LSHIFT || temp->next->next->type != TYPE_RSHIFT
						|| temp->next->next->type != TYPE_WORD || temp->next->next->type != TYPE_HEREDOC || temp->next->next->type != TYPE_APPEND))
						{
						ft_putstr_fd("minishell: syntax error near unexpected token", 2);
						ft_putstr_fd(" `", 2);
						ft_putstr_fd(temp->value, 2);
						ft_putendl_fd("\'", 2);
						(*utils)->code = 2;
						return (0);
						}
				}
				else if (!ft_strcmp(temp->next->value, ">>")
				|| !ft_strcmp(temp->next->value, ">") || !ft_strcmp(temp->next->value, "<")
				|| !ft_strcmp(temp->next->value, "<<"))
				{
					if ((temp->type != TYPE_WORD || temp->type != TYPE_PIPE) && temp->next->next->type != TYPE_WORD)
					{
						ft_putstr_fd("minishell: syntax error near unexpected token", 2);
						ft_putstr_fd(" `", 2);
						ft_putstr_fd(temp->value, 2);
						ft_putendl_fd("\'", 2);
						(*utils)->code = 2;
						return (0);
					} 
				}
				else if (!ft_strcmp(temp->next->value, "||")
				|| !ft_strcmp(temp->next->value, "&&"))
				{
					if (temp->type != TYPE_WORD && temp->next->next->type != TYPE_WORD)
					{
						ft_putstr_fd("minishell: syntax error near unexpected token", 2);
						ft_putstr_fd(" `", 2);
						ft_putstr_fd(temp->value, 2);
						ft_putendl_fd("\'", 2);
						(*utils)->code = 2;
						return (0);
					} 
				}
			} 
		}
		temp = temp->next;
	}
	return (1);
}
