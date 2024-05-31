/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:15:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/05/31 11:58:26 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	handle_this(int sig)
{
	(void)sig;
	ft_printf("\nminishell>");
}*/

void	setup_signal(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		perror("sigemptyset");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &sa, NULL))
		sa.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL))
		ft_printf("\nminishell>");
}
