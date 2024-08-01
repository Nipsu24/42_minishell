/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:18 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/07/31 10:12:00 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Handles execution of a single command and it's arguments and single
  '>' redirection. save_stdout restores in the parent process the
  initial stdout fd.*/
int	exec_cmd(t_data *data)
{
	int	pid;
	int	j;
	int	save_stdout;
	int	fd;
	int	i;

	pid = fork();
	j = 0;
	fd = -1;
	i = 0;
	save_stdout = dup(STDOUT_FILENO);
	if (pid == 0)
	{
		if (data->proc[j].redir && data->proc[j].redir[i])
		{
			if (ft_strncmp(data->proc[j].redir[i], ">", 1) == 0)
			{
				fd = open(data->proc[j].redir[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd < 0)
				{
					perror("open");
					return (1);
				}
				dup2(fd, STDOUT_FILENO);
				close (fd);
			}
		}
		if (execve(data->proc[j].path, data->proc[j].cmd, data->temp_env) == -1)
			printf("%s: command not found\n", data->proc[j].cmd[0]);
	}
	waitpid(pid, NULL, 0);
	dup2(save_stdout, STDOUT_FILENO);
	close (save_stdout);	
	return (0);
}