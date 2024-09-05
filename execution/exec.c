/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:18:32 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/05 22:53:48 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Initialises variables needed for execution*/
static int	init_exec(t_data *data)
{
	init_index(data);
	init_pid_arr(data);
	init_fd_arr(data);
	data->save_stdout = dup(STDOUT_FILENO);
	data->save_stdin = dup(STDIN_FILENO);
	if (data->save_stdout == -1 || data->save_stdin == -1)
	{
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

/*Creates pipes within exec_loop function.*/
static int	create_pipe(t_data *data)
{
	data->pipe_flag = 0;
	if (data->proc_nbr > 1 && data->j != data->proc_nbr -1)
	{
		data->pipe_flag = 1;
		if (pipe(data->fd_arr[data->j]) == -1)
		{
			data->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

/*Forks processes within exec_loop function.*/
static int	fork_procs(t_data *data)
{
	data->pid_arr[data->j] = fork();
	if (data->pid_arr[data->j] == -1)
	{
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

/*Main loop for execution, contains logic of creating pipes,
  forks and command/built-in execution by child processes
  and builtin execution by main process. Main process closes
  not needed fds at end of loop.*/
static int	exec_loop(t_data *data)
{
	while (data->j < data->proc_nbr)
	{
		handle_signals(2);
		if (create_pipe(data))
			return (1);
		if (!non_child_builtins(data))
		{
			if (fork_procs(data))
				return (1);
			handle_signals(1);
			if (data->pid_arr[data->j] == 0)
			{
				if (child_procs(data))
					free_all(data, data->exit_status);
				if (child_exec(data))
					free_all(data, data->exit_status);
				free_all(data, 2);
			}
			if ((data->pid_arr[data->j]) > 0)
				parent_close_fds(data);
		}
		data->j++;
	}
	return (0);
}

/*Handles execution of multiple process and their arguments 
  and multiple '>', '<' '>>' and '<<' redirection. save_stdout/-in
  restores the initial state of stdout/-in in the parent process.*/
int	exec_proc(t_data *data)
{
	if (data->err_flag)
		return (0);
	if (parent_builtin_check(data) && data->proc_nbr > 1)
		return (0);
	if (init_exec(data))
		return (1);
	if (exec_loop(data))
		return (1);
	if (!parent_builtin_check(data))
		parent_wait_n_cleanup(data);
	return (0);
}
