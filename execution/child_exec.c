/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:52:40 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/29 14:58:51 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Hanldes opening/closing of pipe fd for first process*/
static int	child_first_pipe(t_data *data)
{
	close(data->fd_arr[data->j][0]);
	if (dup2(data->fd_arr[data->j][1], STDOUT_FILENO) < 0)
		return (1);
	close(data->fd_arr[data->j][1]);
	return (0);
}

/*Hanldes opening/closing of pipe fds for middle processes*/
static int	child_middle_pipes(t_data *data)
{
	if (dup2(data->fd_arr[data->j - 1][0], STDIN_FILENO) < 0)
		return (1);
	close(data->fd_arr[data->j - 1][0]);
	close(data->fd_arr[data->j][0]);
	if (dup2(data->fd_arr[data->j][1], STDOUT_FILENO) < 0)
		return (1);
	close(data->fd_arr[data->j][1]);
	return (0);
}

/*Hanldes opening/closing of pipe fd for last process*/
static int	child_last_pipe(t_data *data)
{
	close(data->fd_arr[data->j -1][1]);
	if (dup2(data->fd_arr[data->j - 1][0], STDIN_FILENO) < 0)
		return (1);
	close(data->fd_arr[data->j - 1][0]);
	return (0);
}

/*Hanldes heredoc and redirects in child processes, opens/closes
  fds for respective pipes.*/
int	child_procs(t_data *data)
{
	if (heredoc_exec(data))
		return (1);
	if (redir_exec(data))
		return (1);
	if (data->pipe_flag == 1 && data->j == 0)
	{
		if (child_first_pipe(data))
			return (1);
	}
	if (data->pipe_flag == 1 && data->j != 0 && data->j != data->proc_nbr -1)
	{
		if (child_middle_pipes(data))
			return (1);
	}
	if (data->proc_nbr > 1 && data->j != 0 && data->j == data->proc_nbr -1)
	{
		if (child_last_pipe(data))
			return (1);
	}
	return (0);
}

/*Hanldes execution of non-builtin commands by child process.*/
int	child_exec(t_data *data)
{
	if (data->proc[data->j].cmd != NULL)
	{
		if (!child_builtins(data))
		{
			if (execve(data->proc[data->j].path,
					data->proc[data->j].cmd, data->temp_env) == -1)
			{
				printf("%s: command not found\n", data->proc[data->j].cmd[0]);
				data->exit_status = 127;
				return (1);
			}
			else
				data->exit_status = 0;
		}
	}
	return (0);
}
