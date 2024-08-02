/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <mariusmeier@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:18 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/08/02 17:45:49 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns 0 in case another redirect out operator has been found in
  redir array, otherwise returns 1.*/
static int	no_other_redout(t_data *data, int j, int i)
{
	i++;
	while (data->proc[j].redir[i])
	{
		if (ft_strncmp(data->proc[j].redir[i], ">", 1) == 0
			&& !data->proc[j].redir[i][1])
			return (0);
		i++;
	}
	return (1);
}

/*Handles execution of a single command and it's arguments and multiple
  '>' redirection. save_stdout restores in the parent process the
  initial stdout fd.*/
int	exec_cmd(t_data *data)
{
	int	pid;
	int	j;
	int	i;
	int	k;
	int	flag;

	pid = fork();
	j = 0;
	i = 0;
	k = 0;
	flag = 0;
	data->save_stdout = dup(STDOUT_FILENO);
	if (pid == 0)
	{
		if (data->proc[j].redir && data->proc[j].redir[i])
		{
			while (data->proc[j].redir[i])
			{
				if (ft_strncmp(data->proc[j].redir[i], ">", 1) == 0 && !data->proc[j].redir[i][1])
				{
					flag = 1;
					data->proc[j].fd[k] = open(data->proc[j].redir[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (data->proc[j].fd[k] < 0)
					{
						perror("open");
						return (1);
					}
					if (no_other_redout(data, j, i))
					{
						dup2(data->proc[j].fd[k], STDOUT_FILENO);
						close(data->proc[j].fd[k]);
						flag = 0;
					}
					else
						close (data->proc[j].fd[k]);
				}
				if (flag)
				{
					k++;
					flag = 0;
				}
				i++;
			}
		}
		if (execve(data->proc[j].path, data->proc[j].cmd, data->temp_env) == -1)
			printf("%s: command not found\n", data->proc[j].cmd[0]);
	}
	waitpid(pid, NULL, 0);
	dup2(data->save_stdout, STDOUT_FILENO);
	close (data->save_stdout);	
	return (0);
}
