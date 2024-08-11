/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:18 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/08/11 11:19:50 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Handles redirection of heredoc content.*/
static int	heredoc_exec(t_data *data)
{
	if (data->proc[data->j].redir && data->proc[data->j].redir[data->i])
	{
		while (data->proc[data->j].redir[data->l])
		{
			if (here_redirect(data))
				return (1);
			data->l++;
		}
	}
	return (0);
}

/*Handles redirect operants <, > and >>.*/

static int	redir_exec(t_data *data)
{
	if (data->proc[data->j].redir && data->proc[data->j].redir[data->i])
	{
		while (data->proc[data->j].redir[data->i])
		{
			if (redout_loop(data) || redin_loop(data)
				|| appendout_loop(data))
				return (1);
			data->i++;
		}
	}
	return (0);
}

/*Deletes all heredocs created in course of heredoc handling.*/
static void	delete_heredocs(t_data *data)
{
	data->j = 0;
	while (data->j < data->proc_nbr) 
	{
		unlink(data->proc[data->j].here_name);
		data->j++;
	}
}

// static int	init_pid_arr(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	data->pid_arr = malloc (sizeof(int) * data->proc_nbr);
// 	if (!data->pid_arr)
// 		return (1);
// 	while (i < data->proc_nbr)
// 	{
// 		data->pid_arr[i] = -1;
// 		i++;
// 	}
// 	return (0);
// }

// static void	fill_fd_arr(t_data *data)
// {
// 	int j;
// 	int	i;

// 	j = 0;
// 	i = 0;
// 	while (j < data->proc_nbr)
// 	{
// 		data->fd_arr[j][0] = 0;
// 		data->fd_arr[j][1] = 1;
// 		j++;
// 	}
// }

// static int	init_fd_arr(t_data *data)
// {
// 	int j;
// 	int	i;

// 	j = 0;
// 	i = 0;
// 	if (data->proc_nbr < 2)
// 		return (0);
// 	data->fd_arr = malloc (sizeof(int) * (data->proc_nbr - 1));
// 	if (!data->fd_arr)
// 		return (1);
// 	while (j < data->proc_nbr)
// 	{
// 		while (i < 2)
// 		i = 0;
// 		{
// 			data->fd_arr[j][i] = malloc (sizeof(int) * 2);
// 			if (!data->fd_arr[j][i])
// 				return (1);
// 			i++;
// 		}
// 		j++;
// 	}
// 	fill_fd_arr(data);
// 	return (0);	
// }

// /*Handles execution of a single process and it's arguments 
//   and multiple '>', '<' '>>' and '<<' redirection. save_stdout/-in
//   restores the initial state of stdout/-in in the parent process.*/
// int	exec_proc(t_data *data)
// {
// 	int	fd[2];
// 	int	pipe_flag;

// 	pipe_flag = 0;
// 	init_index(data);
// 	init_pid_arr(data);
// 	init_fd_arr(data);
// 	data->save_stdout = dup(STDOUT_FILENO);
// 	data->save_stdin = dup(STDIN_FILENO);
// 	while (data->j < data->proc_nbr)
// 	{
// 		pipe_flag = 0;
// 		if (data->j != data->proc_nbr -1)
// 		{
// 			pipe_flag = 1;
// 			if (pipe(fd) == -1)
// 				return (1);
// 		}
// 		data->pid_arr[data->j] = fork();
// 		if (data->pid_arr[data->j] == 0)
// 		{
// 			if (heredoc_exec(data))
// 				exit(EXIT_FAILURE);
// 			if (redir_exec(data))
// 				exit(EXIT_FAILURE);
// 			if (ft_strncmp(data->proc[data->j].cmd[0], "builtin", 7) == 0) // insert link to builint part line below
// 				printf("BUILTIN PART\n");
// 			else
// 			{
// 				if (pipe_flag == 1)
// 				{
// 					dup2(data->fd_arr[data->j][1], STDOUT_FILENO);
// 					close(data->fd_arr[data->j][0]);
// 					close(data->fd_arr[data->j][1]);
// 				}
// 				if (execve(data->proc[data->j].path,
// 						data->proc[data->j].cmd, data->temp_env) == -1)
// 					printf("%s: command not found\n", data->proc[data->j].cmd[0]);
// 			}
// 			exit(EXIT_SUCCESS);
// 		}
// 		data->i = 0;
// 		data->l = 0;
// 		data->j++;
// 	}
// 	waitpid(data->pid_arr[data->j], NULL, 0);
// 	delete_heredocs(data);
// 	dup2(data->save_stdout, STDOUT_FILENO);
// 	dup2(data->save_stdin, STDIN_FILENO);
// 	close (data->save_stdout);
// 	close (data->save_stdin);
// 	return (0);
// }


int	exec_proc(t_data *data)
{
	int	pid;

	init_index(data);
	pid = fork();
	data->save_stdout = dup(STDOUT_FILENO);
	data->save_stdin = dup(STDIN_FILENO);
	if (pid == 0)
	{
		if (heredoc_exec(data))
			exit(EXIT_FAILURE);
		if (redir_exec(data))
			exit(EXIT_FAILURE);
		if (ft_strncmp(data->proc[data->j].cmd[0], "builtin", 7) == 0) // insert link to builint part line below
			printf("BUILTIN PART\n");
		else
		{
			if (execve(data->proc[data->j].path,
					data->proc[data->j].cmd, data->temp_env) == -1)
				printf("%s: command not found\n", data->proc[data->j].cmd[0]);
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	delete_heredocs(data);
	dup2(data->save_stdout, STDOUT_FILENO);
	dup2(data->save_stdin, STDIN_FILENO);
	close (data->save_stdout);
	close (data->save_stdin);
	return (0);
}