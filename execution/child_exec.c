/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:52:40 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/12 15:51:19 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Hanldes opening/closing of pipe fd for first process*/
static int	child_first_pipe(t_data *data)
{
	close(data->fd_arr[data->j][0]);
	if (data->proc_nbr > 1) // new
	{
		if (dup2(data->fd_arr[data->j][1], STDOUT_FILENO) < 0)
			return (1);
	}
	close(data->fd_arr[data->j][1]);
	close(data->save_stdout); // new
	close(data->save_stdin); //new
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
	close(data->save_stdout); // new
	close(data->save_stdin); // new
	return (0);
}

/*Hanldes opening/closing of pipe fd for last process*/
static int	child_last_pipe(t_data *data)
{
	close(data->fd_arr[data->j - 1][1]);
	if (dup2(data->fd_arr[data->j - 1][0], STDIN_FILENO) < 0)
		return (1);
	close(data->fd_arr[data->j - 1][0]);
	close(data->fd_arr[data->j][0]); //new
	close(data->fd_arr[data->j][1]); //new
	close(data->save_stdout); // new
	close(data->save_stdin); // new
	return (0);
}

/*Hanldes heredoc and redirects in child processes, opens/closes
  fds for respective pipes.*/
int	child_procs(t_data *data)
{
	handle_signals(2);
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
			if (!data->proc[data->j].path)
			{
				update_exit_status(data, 127, data->proc[data->j].cmd[0],
					"Command not found");
				return (1);
			}
			else
			{
				if (execve(data->proc[data->j].path,
						data->proc[data->j].cmd, data->temp_env) == -1)
				{
					update_exit_status(data, 126, NULL,
						"Command not executable");
					return (1);
				}
				else
					data->exit_status = 0;
			}
		}
	}
	return (0);
}
