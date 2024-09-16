/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:54:59 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/16 22:21:08 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to check if the command is a child builtin. If it is, execute the
   builtin and return 1. */
int	child_builtins(t_data *data)
{
	if (!data->proc[data->j].cmd)
		return (0);
	if (ft_strncmp(data->proc[data->j].cmd[0], "echo", 5) == 0)
		return (echo(data), 1);
	else if (ft_strncmp(data->proc[data->j].cmd[0], "env", 4) == 0)
		return (print_env(data), 1);
	else if (ft_strncmp(data->proc[data->j].cmd[0], "pwd", 4) == 0)
		return (pwd(data), 1);
	return (0);
}

/* Function to check if the command is a non-child builtin. If it is, execute
the builtin and return 1. */
int	non_child_builtins(t_data *data)
{
	if (!data->proc[data->j].cmd)
		return (0);
	if (ft_strncmp(data->proc[data->j].cmd[0], "cd", 3) == 0)
		return (cd(data->proc[data->j].cmd, data), 1);
	else if (ft_strncmp(data->proc[data->j].cmd[0], "exit", 5) == 0)
		return (do_exit(data), 1);
	else if (ft_strncmp(data->proc[data->j].cmd[0], "export", 7) == 0)
		return (export(data), 1);
	else if (ft_strncmp(data->proc[data->j].cmd[0], "unset", 6) == 0)
	{
		if (!data->proc[data->j].cmd[1])
			return (update_exit_status(data, 0, NULL, NULL), -1);
		return (unset(data), 1);
	}
	return (0);
}

/* Function to check if the command is a builtin */
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
