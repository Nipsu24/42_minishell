/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:18 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/08/20 14:50:37 by cesasanc         ###   ########.fr       */
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

/*Handles execution of multiple process and their arguments 
  and multiple '>', '<' '>>' and '<<' redirection. save_stdout/-in
  restores the initial state of stdout/-in in the parent process.*/
int	exec_proc(t_data *data)
{
	int	pipe_flag;
	int	n;

	n = 0;
	pipe_flag = 0;
	init_index(data);
	init_pid_arr(data);
	init_fd_arr(data);
	data->save_stdout = dup(STDOUT_FILENO);
	data->save_stdin = dup(STDIN_FILENO);
	if (data->save_stdout == -1 || data->save_stdin == -1)
		return (1);
	while (data->j < data->proc_nbr)
	{
		pipe_flag = 0;
		if (data->proc_nbr > 1 && data->j != data->proc_nbr -1)
		{
			pipe_flag = 1;
			if (pipe(data->fd_arr[data->j]) == -1)
				return (1);
		}
		non_child_builtins(data);
		data->pid_arr[data->j] = fork();
		if (data->pid_arr[data->j] == -1)
			return (1);
		if (data->pid_arr[data->j] == 0)
		{
			if (heredoc_exec(data))
				free_all(data, 1);
			if (redir_exec(data))
				free_all(data, 1);
			if (pipe_flag == 1 && data->j == 0)
			{
				if (dup2(data->fd_arr[data->j][1], STDOUT_FILENO) == -1)
					free_all(data, 1);				
			}
			if (pipe_flag == 1 && data->j != 0 && data->j != data->proc_nbr -1)
			{
				if (dup2(data->fd_arr[data->j - 1][0], STDIN_FILENO) == -1)
					free_all(data, 1);
				if (dup2(data->fd_arr[data->j][1], STDOUT_FILENO) == -1)
					free_all(data, 1);
			}
			if (data->proc_nbr > 1 && data->j != 0 && data->j == data->proc_nbr -1)
				if (dup2(data->fd_arr[data->j -1][0], STDIN_FILENO) == -1)
					free_all(data, 1);
			while (n < data->j)
			{
				close(data->fd_arr[n][0]);
				close(data->fd_arr[n][1]);
				n++;
			}
			
			if (!child_builtins(data))
			{
				if (data->proc[data->j].path != NULL && data->proc[data->j].cmd != NULL)
				{
					if (execve(data->proc[data->j].path,
						data->proc[data->j].cmd, data->temp_env) == -1)
					{
						printf("%s: command not found\n", data->proc[data->j].cmd[0]);
						free_all(data, 1);
					}
				
				}
			}
			free_all(data, 2);
		}
		if ((data->pid_arr[data->j]) > 0)
			waitpid(data->pid_arr[data->j], NULL, 0);
		data->j++;
	}
	//waitpid(data->pid_arr[data->j], NULL, 0);
	delete_heredocs(data);
	dup2(data->save_stdout, STDOUT_FILENO);
	dup2(data->save_stdin, STDIN_FILENO);
	close (data->save_stdout);
	close (data->save_stdin);
	return (0);
}


//old version of exec_proc//

// int	exec_proc(t_data *data)
// {
// 	int	pid;

// 	init_index(data);
// 	pid = fork();
// 	data->save_stdout = dup(STDOUT_FILENO);
// 	data->save_stdin = dup(STDIN_FILENO);
// 	if (pid == 0)
// 	{
// 		if (heredoc_exec(data))
// 			exit(EXIT_FAILURE);
// 		if (redir_exec(data))
// 			exit(EXIT_FAILURE);
// 		if (ft_strncmp(data->proc[data->j].cmd[0], "builtin", 7) == 0) // insert link to builint part line below
// 			printf("BUILTIN PART\n");
// 		else
// 		{
// 			if (execve(data->proc[data->j].path,
// 					data->proc[data->j].cmd, data->temp_env) == -1)
// 				printf("%s: command not found\n", data->proc[data->j].cmd[0]);
// 		}
// 		exit(EXIT_SUCCESS);
// 	}
// 	waitpid(pid, NULL, 0);
// 	delete_heredocs(data);
// 	dup2(data->save_stdout, STDOUT_FILENO);
// 	dup2(data->save_stdin, STDIN_FILENO);
// 	close (data->save_stdout);
// 	close (data->save_stdin);
// 	return (0);
// }

int	child_builtins(t_data *data)
{
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
		pwd();
		return (1);
	}
	return (0);
}

void	non_child_builtins(t_data *data)
{
	if (ft_strncmp(data->proc[data->j].cmd[0], "cd", 3) == 0)
		cd(data->proc[data->j].cmd, data);
	else if (ft_strncmp(data->proc[data->j].cmd[0], "exit", 5) == 0)
		do_exit(data);
	else if (ft_strncmp(data->proc[data->j].cmd[0], "export", 7) == 0)
		export(data);
	else if (ft_strncmp(data->proc[data->j].cmd[0], "unset", 6) == 0)
		unset(data);
}
