/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:15:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/29 18:56:28 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		ioctl(0, TIOCSTI, "\n");
	}
	else if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
}*/

static void	ignore(int sig)
{
	if (sig == SIGINT)
	{
	rl_replace_line("", 1);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	}
}

void	setup_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ignore);
}
