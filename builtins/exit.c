/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:44:12 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/22 11:07:11 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

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

int	do_exit(t_data *data)
{
	if (!data->proc[data->j].cmd[1])
	{
		printf("exit\n");
		exit(data->exit_status);
	}
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
			printf("minishell: exit: %s: numeric argument required\n",
			 data->proc[data->j].cmd[1]);
			data->exit_status = 255;
			return (data->exit_status);
		}
		data->exit_status = ft_atoi(data->proc[data->j].cmd[1]);
		printf("exit\n");
		exit(data->exit_status);
	}
	return (data->exit_status);
}
