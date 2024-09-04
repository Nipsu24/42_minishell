/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:15:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/04 15:29:45 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_int(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

static void	ignore(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signals(int flag)
{
	if (flag == 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, sig_int);
	}
	else if (flag == 2)
	{
		signal(SIGINT, SIG_DFL);
	}
}

void	setup_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ignore);
}

void	here_sig_int(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_sigint = true;
		close(STDIN_FILENO);
	}
}
