/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:03:42 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/17 16:21:50 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to print an error message. If cmd is not NULL, print the command
   name. If str is not NULL, print the error message. */
void	print_error(char *cmd, char *str)
{
	if (cmd)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
	}
	if (str)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

/* Function to update the exit status. If cmd or msg is not NULL, print the
error message. Then update the exit status with the given status. */
int	update_exit_status(t_data *data, int status, char *cmd, char *msg)
{
	if (cmd || msg)
		print_error(cmd, msg);
	data->exit_status = status;
	return (status);
}

/* Function to initialize the index variables. */
void	init_index(t_data *data)
{
	data->j = 0;
	data->i = 0;
	data->k = 0;
	data->l = 0;
	data->m = 0;
}

/*Checks if a character is enclosed by both, single and double quotes.*/
int	in_both_quotes(char *input, int pos)
{
	int	count;

	count = 0;
	if ((count_d_quotes_left(input, pos) == 1)
		&& (count_d_quotes_right(input, pos) != 0))
		count++;
	if ((count_s_quotes_left(input, pos) == 1)
		&& (count_s_quotes_right(input, pos) != 0))
		count++;
	return (count);
}
