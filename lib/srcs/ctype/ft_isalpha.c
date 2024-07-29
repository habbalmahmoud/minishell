/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:17:47 by nkanaan           #+#    #+#             */
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

int	ft_isalpha(int c)
{
	if (!(test_for_alpha(c)))
	{
		return (0);
	}
	return (1);
}
// int	main(void)
// {
// 	int s;

// 	s = 80;

// 	printf("%d", ft_isalpha(s));
// 	return (0);
// }
