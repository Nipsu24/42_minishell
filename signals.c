/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:15:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/05/30 15:18:56 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_this(int sig)
{
	(void)sig;
	ft_printf("\nminishell>");
}

void	setup_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_this;
	sa_int.sa_flags = SA_RESTART;
	if (sigemptyset(&sa_int.sa_mask) == -1)
	{
		perror("sigemptyset");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction: SIGINT");
		exit(EXIT_FAILURE);
	}
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	if (sigemptyset(&sa_quit.sa_mask) == -1)
	{
		perror("sigemptyset");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("sigaction: SIGQUIT");
		exit(EXIT_FAILURE);
	}
}