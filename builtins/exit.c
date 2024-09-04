/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:44:12 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/04 10:20:37 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if the argument is a number. */
static bool	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (false);
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		if (!str[i])
			return (false);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/* Checks if the argument is an overflow. */
static bool	exit_overflow(const char *str)
{
	if (ft_strlen(str) > 20)
		return (true);
	if (ft_strlen(str) == 19
		&& ft_strncmp(str, "9223372036854775807", ft_strlen(str)) > 0)
		return (true);
	if (ft_strlen(str) == 20
		&& ft_strncmp(str, "-9223372036854775808", ft_strlen(str)) > 0)
		return (true);
	return (false);
}

/* The exit command. If there are more than 2 arguments, print an error message.
If there is one argument, check if it is a number and if it is an overflow.
If it is, print an error message. If it is not, convert the argument to an int
and exit with that status. If there are no arguments, exit with status 0. */
int	do_exit(t_data *data)
{
	if (data->proc[data->j].cmd[1] && data->proc[data->j].cmd[2])
	{
		printf("exit: too many arguments\n");
		data->exit_status = 1;
		return (data->exit_status);
	}
	if (data->proc[data->j].cmd[1])
	{
		if (!is_numeric(data->proc[data->j].cmd[1])
			|| exit_overflow(data->proc[data->j].cmd[1]))
		{
			write(STDERR_FILENO, "minishell: exit: , ", 19);
			write(STDERR_FILENO, data->proc[data->j].cmd[1],
				ft_strlen(data->proc[data->j].cmd[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 29);
			data->exit_status = 255;
			return (data->exit_status);
		}
		data->exit_status = ft_atoi(data->proc[data->j].cmd[1]);
	}
	write(STDERR_FILENO, "exit\n", 5);
	exit(data->exit_status);
}
