/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:15:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/09 12:54:55 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to handle SIGINT signal. If the signal is SIGINT, print a new line.
   This function is used in the ignore function. */
static void	sig_int(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

/* Function to ignore SIGINT signal. If the signal is SIGINT, replace the line
   with an empty string, print a new line and redisplay the prompt. */
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

/* Function to handle signals. If the flag is 1, ignore SIGQUIT and SIGINT
signals and handle SIGINT signal. If the flag is 2, restore the default
behavior of SIGINT and SIGQUIT signals. */
void	handle_signals(int flag)
{
	if (flag == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, sig_int);
	}
	else if (flag == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

/* Function to setup signals. Ignore SIGQUIT signal and call the ignore function
   when the SIGINT signal is received. */
void	setup_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ignore);
}

/* Function to handle SIGINT signal. If the signal is SIGINT, print a new line
   and set the global variable g_sigint to true. */
void	here_sig_int(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_sigint = true;
		close(STDIN_FILENO);
	}
}
