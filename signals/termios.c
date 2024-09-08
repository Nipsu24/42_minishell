/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:23:43 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/08 21:44:35 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to setup termios. If mode is 0, set the terminal to non-canonical
   mode. If mode is 1, restore the terminal to canonical mode. */
void	setup_termios(int mode)
{
	static struct termios	term;

	if (mode == 0)
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~(ICANON | ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	else if (mode == 1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		term.c_lflag |= ICANON | ECHO;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}
