/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:23:25 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:18 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	test_for_alpha(int c)
{
	if ((c >= 'A') && (c <= 'Z'))
	{
		return (1);
	}
	else if ((c >= 'a') && (c <= 'z'))
	{
		return (1);
	}
	return (0);
}

int	test_for_digit(int c)
{
	if ((c >= '0') && (c <= '9'))
	{
		return (1);
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if (!(test_for_alpha(c)) && !(test_for_digit(c)))
	{
		return (0);
	}
	return (1);
}
