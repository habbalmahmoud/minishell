/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_syntax.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:10:02 by nbk               #+#    #+#             */
/*   Updated: 2024/09/09 09:16:13 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"
#include "../../../includes/execute.h"

static int	validate_single(t_token *temp, t_exec_utils **utils)
{
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
	return (1);
}

static int	validate_paren(t_token *temp, t_exec_utils **utils)
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
	return (1);
}

static int	validate_semicol(t_token *temp, t_exec_utils **utils)
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
	return (1);
}

static int	validate_helper(t_token *temp, t_exec_utils **utils)
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
	if (!post_pipe(temp, utils))
		return (0);
	else if (!ft_strcmp(temp->next->value, ">>")
		|| !ft_strcmp(temp->next->value, ">")
		|| !ft_strcmp(temp->next->value, "<")
		|| !ft_strcmp(temp->next->value, "<<"))
	{
		if (!post_redir(temp, utils))
			return (0);
	}
	else if (!ft_strcmp(temp->next->value, "||")
		|| !ft_strcmp(temp->next->value, "&&"))
		if (!post_and_or(temp, utils))
			return (0);
	return (1);
}

int	validate_lexer(t_lexer **lex, t_exec_utils **utils)
{
	t_token	*temp;

	temp = (*lex)->token_list;
	if (!validate_single(temp, utils))
		return (0);
	while (temp)
	{
		if (!validate_paren(temp, utils))
			return (0);
		if (temp->next)
		{
			if (!validate_semicol(temp, utils))
				return (0);
			if (temp->next->type == TYPE_PIPE
				|| temp->next->type == TYPE_OR || temp->next->type == TYPE_AND
				|| temp->next->type == TYPE_APPEND
				|| temp->next->type == TYPE_RSHIFT
				|| temp->next->type == TYPE_LSHIFT
				|| temp->next->type == TYPE_HEREDOC)
				if (!validate_helper(temp, utils))
					return (0);
		}
		temp = temp->next;
	}
	return (1);
}
