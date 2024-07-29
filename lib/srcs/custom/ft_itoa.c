/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:28:37 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:18 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	get_len(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		++i;
	while (n)
	{
		n /= 10;
		++i;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	len;

	len = get_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n == 0)
		res[0] = '0';
	else if (n < 0)
		res[0] = '-';
	while (n)
	{	
		if (n < 0)
			res[--len] = (~(n % 10) + 1) + '0';
		else
			res[--len] = (n % 10) + '0';
		n = n / 10;
	}	
	return (res);
}
// #include <stdio.h>
// #include <limits.h>
// int main()
// {
//   char *str = ft_itoa(-2134);
//   printf("%s\n", str);
//    free(str);
//   str = ft_itoa(42);
//   printf("%s\n", str);
//    free(str);
//   str = ft_itoa(707);
//   printf("%s\n", str);
//    free(str);
//   str = ft_itoa(INT_MIN);
//   printf("%s\n", str);
//    free(str);
//   str = ft_itoa(INT_MAX);
//   printf("%s\n", str); 
//    free(str);
//   str = ft_itoa(0);
//   printf("%s\n", str);
//   free(str);
//   return 0;
// }
