/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:15:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/05/29 18:23:27 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_this(pid_t sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	(void)sig;
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
}

void	setup_signal(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_this;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
//	if (sigemptyset(&sa.sa_mask) == -1);
//		clean_exit_shell();
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		sa.sa_handler = SIG_IGN;
}
