/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:18 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/08/09 16:05:38 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Hanldes redirection of heredoc content.*/
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

/*Hanldes redirect operants <, > and >>.*/

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
	data->m = 0;
	while (data->temp_here[data->m] != NULL)
	{
		unlink(data->temp_here[data->m]);
		data->m++;
	}
}

/*Handles execution of a single process and it's arguments 
  and multiple '>', '<' '>>' and '<<' redirection. save_stdout/-in
  restores the initial state of stdout/-in in the parent process.*/
int	exec_proc(t_data *data)
{
	int	pid;

	pid = fork();
	init_index(data);
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
