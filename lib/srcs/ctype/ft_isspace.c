/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:01:40 by nbk               #+#    #+#             */
/*   Updated: 2024/09/03 15:15:59 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ctype.h"

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (0);
	return (1);
}
