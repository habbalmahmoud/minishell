/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:56:47 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/08 13:52:34 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../../includes/lexer.h"
# include "../../../includes/token.h"

int	assign_type(char c)
{
	if (c == ' ' || c == '\t' || c == '\\' || c == '\n')
		return (return_whitespaces(c));
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == ';')
		return (return_operators(c));
	if (c == 34 || c == 39 || c == '(' || c == ')' || c == '=')
		return (return_literals(c));
	if (c == 0)
		return (TYPE_NULL);
	else
		return (TYPE_WORD);
}

void	init_token(t_token *token, int n, int id)
{
	token->value = ft_calloc(1, n + 1);
	token->value[0] = '\0';
	token->type = TYPE_NULL;
	token->id = id + 1;
	token->next = NULL;
}

void	free_token_ll(t_token *token)
{
	if (token)
	{
		free(token->value);
		free_token_ll(token->next);
		free(token);
	}
}

