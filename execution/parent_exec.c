/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:38:53 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/28 15:54:31 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		close(data->fd_arr[data->j -1][1]);
	}
}

void	parent_wait_n_cleanup(t_data *data)
{
	int	n;
	int	status;

	n = 0;
	while (n < data->proc_nbr)
	{
		waitpid(data->pid_arr[n], &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		n++;
	}
	delete_heredocs(data);
	dup2(data->save_stdout, STDOUT_FILENO);
	dup2(data->save_stdin, STDIN_FILENO);
	close (data->save_stdout);
	close (data->save_stdin);
}
