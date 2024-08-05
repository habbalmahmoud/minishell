/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_paran_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:36:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/05 11:41:58 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_paran(t_lexer *lex, t_token *token, int *state, int type)
{
	if (type == TYPE_RPAREN && (*state) != IN_PARAN)
}