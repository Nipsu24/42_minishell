/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:38:53 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/06 11:52:02 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Contains logic of closing not needed fds of the several pipes.*/
void	parent_close_fds(t_data *data)
{
	if (data->pipe_flag && data->j == 0)
		close(data->fd_arr[data->j][1]);
	if (data->pipe_flag && data->j > 0 && data->j != data->proc_nbr -1)
	{
		close(data->fd_arr[data->j - 1][0]);
		close(data->fd_arr[data->j][1]);
	}
	if (data->pipe_flag && data->j > 0 && data->j == data->proc_nbr -1)
	{
		close(data->fd_arr[data->j - 1][0]);
		close(data->fd_arr[data->j - 1][1]);
		close(data->fd_arr[data->j][0]); //new
		close(data->fd_arr[data->j][1]); //new
	}
}

/*Extracts exit_status from child processes, deletes heredocs
  and resets stdin and stdout fds.*/
void	parent_wait_n_cleanup(t_data *data)
{
	int	n;
	int	status;
	int	child_exit_status;

	n = 0;
	child_exit_status = 0;
	while (n < data->proc_nbr)
	{
		waitpid(data->pid_arr[n], &status, 0);
		if (WIFEXITED(status))
		{
			child_exit_status = WEXITSTATUS(status);
			if (child_exit_status != 0)
				data->exit_status = child_exit_status;
		}
		n++;
	}
	delete_heredocs(data);
	dup2(data->save_stdout, STDOUT_FILENO);
	dup2(data->save_stdin, STDIN_FILENO);
	close (data->save_stdout);
	close (data->save_stdin);
}

