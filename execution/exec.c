/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <mariusmeier@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:18 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/08/08 14:13:26 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_exec(t_data *data)
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
	return (0);
}

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
			return (1);
		if (redir_exec(data))
			return (1);
		if (ft_strncmp(data->proc[data->j].cmd[0], "builtin", 7) == 0) // insert link to builint part line below
			printf("BUILTIN PART\n");
		else
		{
			if (execve(data->proc[data->j].path,
					data->proc[data->j].cmd, data->temp_env) == -1)
				printf("%s: command not found\n", data->proc[data->j].cmd[0]);
		}
	}
	waitpid(pid, NULL, 0);
	dup2(data->save_stdout, STDOUT_FILENO);
	dup2(data->save_stdin, STDIN_FILENO);
	//heredoc files maybe to be deleted here (also need for rename files to make them invisible)
	close (data->save_stdout);
	close (data->save_stdin);
	return (0);
}
