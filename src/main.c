/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:02:37 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/08 14:37:19 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// #include "./sig_guard/sig_guard.h"


int	main(int ac, char **av, char **env)
{
	char	**c_env;

	c_env = copy_2d_array(env);
	if (ac != 1)
		exit(printf("Invalid args\n"));
	else
		init_shell(c_env);
}
