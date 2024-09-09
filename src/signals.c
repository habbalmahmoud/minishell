/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 02:44:47 by nbk               #+#    #+#             */
/*   Updated: 2024/09/09 02:44:48 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include "../includes/signals.h"

void	handle_signint(int signum)
{
	g_mini_code = 130;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	fork_handler(int signum)
{
	if (signum == 2)
		g_mini_code = 130;
	else
	{
		ft_putstr_fd("exit", 1);
		g_mini_code = 131;
	}
	write(1, "\n", 1);
}

void	signal_handler(void)
{
	signal(SIGINT, handle_signint);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_heredoc(int signal_number)
{
	g_mini_code = 52;
	exit(130);
}
