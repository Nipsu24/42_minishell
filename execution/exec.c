/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:18 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/08/06 09:56:58 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Handles execution of a single process and it's arguments 
  and multiple '>', '<' and '>>' redirection. save_stdout/-in
  restores in the parent process the initial state of stdout/-in.*/
int	exec_proc(t_data *data)
{
	int	pid;

	pid = fork();
	data->j = 0;
	data->i = 0;
	data->k = 0;
	data->l = 0;
	data->save_stdout = dup(STDOUT_FILENO);
	data->save_stdin = dup(STDIN_FILENO);
	if (pid == 0)
	{
		if (data->proc[data->j].redir && data->proc[data->j].redir[data->l])
		{
			while (data->proc[data->j].redir[data->l])
			{
				if (ft_heredoc(data))
					return (1);
				data->l++;
			}
		}
		// if (data->proc[data->j].redir && data->proc[data->j].redir[data->i])
		// {
		// 	while (data->proc[data->j].redir[data->i])
		// 	{
		// 		if (redout_loop(data) || redin_loop(data)
		// 			|| appendout_loop(data))
		// 			return (1);
		// 		data->i++;
		// 	}
		// }
		// if (ft_strncmp(data->proc[data->j].cmd[0], "builtin", 7) == 0) // insert link to builint part line below
		// 	printf("BUILTIN PART\n");
		// else
		// {
		// 	if (execve(data->proc[data->j].path,
		// 			data->proc[data->j].cmd, data->temp_env) == -1)
		// 		printf("%s: command not found\n", data->proc[data->j].cmd[0]);
		// }
	}
	waitpid(pid, NULL, 0);
	dup2(data->save_stdout, STDOUT_FILENO);
	dup2(data->save_stdin, STDIN_FILENO);
	close (data->save_stdout);
	close (data->save_stdin);
	return (0);
}



// int	exec_proc(t_data *data)
// {
// 	int	pid;

// 	pid = fork();
// 	data->j = 0;
// 	data->i = 0;
// 	data->k = 0;
// 	data->save_stdout = dup(STDOUT_FILENO);
// 	data->save_stdin = dup(STDIN_FILENO);
// 	if (pid == 0)
// 	{
// 		if (data->proc[data->j].redir && data->proc[data->j].redir[data->i])
// 		{
// 			while (data->proc[data->j].redir[data->i])
// 			{
// 				if (redout_loop(data) || redin_loop(data)
// 					|| appendout_loop(data))
// 					return (1);
// 				data->i++;
// 			}
// 		}
// 		if (ft_strncmp(data->proc[data->j].cmd[0], "builtin", 7) == 0) // insert link to builint part line below
// 			printf("BUILTIN PART\n");
// 		else
// 		{
// 			if (execve(data->proc[data->j].path,
// 					data->proc[data->j].cmd, data->temp_env) == -1)
// 				printf("%s: command not found\n", data->proc[data->j].cmd[0]);
// 		}
// 	}
// 	waitpid(pid, NULL, 0);
// 	dup2(data->save_stdout, STDOUT_FILENO);
// 	dup2(data->save_stdin, STDIN_FILENO);
// 	close (data->save_stdout);
// 	close (data->save_stdin);
// 	return (0);
// }
