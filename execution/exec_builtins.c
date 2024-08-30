/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:54:59 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/30 16:56:39 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_builtins(t_data *data)
{
	if (!data->proc[data->j].cmd)
		return (0);
	if (ft_strncmp(data->proc[data->j].cmd[0], "echo", 5) == 0)
	{
		echo(data);
		return (1);
	}
	else if (ft_strncmp(data->proc[data->j].cmd[0], "env", 4) == 0)
	{
		print_env(data);
		return (1);
	}
	else if (ft_strncmp(data->proc[data->j].cmd[0], "pwd", 4) == 0)
	{
		pwd(data);
		return (1);
	}
	return (0);
}

int	non_child_builtins(t_data *data)
{
	if (!data->proc[data->j].cmd)
		return (0);
	if (ft_strncmp(data->proc[data->j].cmd[0], "cd", 3) == 0)
	{
		cd(data->proc[data->j].cmd, data);
		return (1);
	}
	else if (ft_strncmp(data->proc[data->j].cmd[0], "exit", 5) == 0)
	{
		do_exit(data);
		return (1);
	}
	else if (ft_strncmp(data->proc[data->j].cmd[0], "export", 7) == 0)
	{
		export(data);
		return (1);
	}
	else if (ft_strncmp(data->proc[data->j].cmd[0], "unset", 6) == 0)
	{
		unset(data);
		return (1);
	}
	return (0);
}

int	parent_builtin_check(t_data *data)
{
	data->j = 0;
	while (data->j < data->proc_nbr)
	{
		if (!data->proc[data->j].cmd)
			return (0);
		if (ft_strncmp(data->proc[data->j].cmd[0], "cd", 3) == 0)
			return (1);
		else if (ft_strncmp(data->proc[data->j].cmd[0], "exit", 5) == 0)
			return (1);
		else if (ft_strncmp(data->proc[data->j].cmd[0], "export", 7) == 0)
			return (1);
		else if (ft_strncmp(data->proc[data->j].cmd[0], "unset", 6) == 0)
			return (1);
		data->j++;
	}
	return (0);
}
