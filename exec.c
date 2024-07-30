/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:18 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/07/30 16:10:21 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_cmd(t_data *data)
{
	int	pid;
	int	j;

	pid = fork();
	j = 0;
	if (pid == 0)
	{
		if (execve(data->proc[j].path, data->proc[j].cmd, data->temp_env) == -1)
			printf("%s: command not found\n", data->proc[j].cmd[0]);
	}
	return (0);
}