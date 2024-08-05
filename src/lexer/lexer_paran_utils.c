/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_paran_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:36:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/05 16:54:53 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_paran(t_lexer *lex, t_token **token, int *state, int type)
{
	int len;

	len = ft_strlen(lex->util->input);
	if (type == TYPE_RPAREN && (*state) != IN_PARAN && lex->util->rec_count > 0)
	{
		lex->util->rec_count -= 1;
		return (1);
	}
	if (type == TYPE_RPAREN && (*state) == STATE_ANY && lex->util->rec_count == 0)
		exit(2);
	if (type == TYPE_LPAREN)
	{
		t_lexer	sub_lexer;
		int	len;

		len = ft_strlen(lex->util->input);
		if (lex->util->j > 0)
		{
			(*token)->value[lex->util->j] = '\0';
			(*token)->next = ft_calloc(1, sizeof(t_token));
			if ((*token)->next == NULL)
				return (0);
			*token = (*token)->next;
			init_token((*token), len - lex->util->i);
			lex->util->j = 0;
		}
		// printf("ONE: %c\n", lex->util->c);
		(*token)->value[lex->util->j++] = lex->util->c;
		printf("%c\n", (*token)->value[lex->util->j]);
		(*token)->type = type;
		lex->util->rec_count += 1;
		(*state) = IN_PARAN;
		lex->util->c_input++;
		sub_lexer.util = malloc(sizeof(t_lex_utils));
		sub_lexer.util->rec_count = lex->util->rec_count;
		init_lexer(lex->util->c_input, ft_strlen(lex->util->c_input), &sub_lexer, &(*token)->sub_token);
		lex->util->c_input += sub_lexer.util->i;	
		// printf("THREE: %c\n", *lex->util->c_input);
		if (*lex->util->c_input == ')' && (*state) == IN_PARAN)
		{
			// printf("TWO: %c\n", lex->util->c);
			(*state) = STATE_ANY;
			(*token)->value[lex->util->j++] = TYPE_RPAREN;
			(*token)->value[lex->util->j] = '\0';
			(*token)->next = ft_calloc(1, sizeof(t_token));
			if ((*token)->next == NULL)
				return (0);
			*token = (*token)->next;
			init_token((*token), len - lex->util->i);
			lex->util->j = 0;
		}
	}
	return (0);
}


// fjgwivbf lewf(lewlfw)lk(nwq)ldnlfknwelnf(nkjwefkj(flkwlfew)fjewbjk))