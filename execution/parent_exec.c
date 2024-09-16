/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:38:53 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/16 14:23:15 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Contains logic of closing not needed fds of the several pipes.*/
void	parent_close_fds(t_data *data)
{
	if (data->pipe_flag && data->j == 0)
	{
		close(data->fd_arr[data->j][1]);
		if (data->proc_nbr < 2)
			close(data->fd_arr[data->j][0]);
	}
	if (data->pipe_flag && data->j > 0 && data->j != data->proc_nbr -1)
	{
		close(data->fd_arr[data->j - 1][0]);
		close(data->fd_arr[data->j][1]);
	}
	if (data->pipe_flag && data->j > 0 && data->j == data->proc_nbr -1)
	{
		close(data->fd_arr[data->j - 1][0]);
		close(data->fd_arr[data->j - 1][1]);
		close(data->fd_arr[data->j][0]);
		close(data->fd_arr[data->j][1]);
	}
}

/* Checks if the child process has been terminated by SIGQUIT signal. If so,
it checks its status and prints the correct quit message */
static void	handle_quit(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	if (sig == SIGQUIT)
	{
		if (WCOREDUMP(status))
			print_error(NULL, "Quit (core dumped)");
		else
			print_error(NULL, "Quit");
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
	while (n < data->proc_nbr)
	{
		waitpid(data->pid_arr[n], &status, 0);
		if (WIFSIGNALED(status))
			handle_quit(status);
		if (WIFEXITED(status))
		{
			child_exit_status = WEXITSTATUS(status);
			data->exit_status = child_exit_status;
		}
		else if (WIFSIGNALED(status))
			data->exit_status = 128 + WTERMSIG(status);
		n++;
	}
	delete_heredocs(data);
	dup2(data->save_stdout, STDOUT_FILENO);
	dup2(data->save_stdin, STDIN_FILENO);
	close (data->save_stdout);
	close (data->save_stdin);
}
