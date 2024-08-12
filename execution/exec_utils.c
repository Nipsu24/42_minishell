/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:48:28 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/12 11:05:51 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Deletes all heredocs created in course of heredoc handling.*/
void	delete_heredocs(t_data *data)
{
	data->j = 0;
	while (data->j < data->proc_nbr) 
	{
		unlink(data->proc[data->j].here_name);
		data->j++;
	}
}

/*Initialised int array for process ids, needed for forking
  processes.*/
int	init_pid_arr(t_data *data)
{
	int	i;

	i = 0;
	data->pid_arr = malloc (sizeof(int) * data->proc_nbr);
	if (!data->pid_arr)
		return (1);
	while (i < data->proc_nbr)
	{
		data->pid_arr[i] = -1;
		i++;
	}
	return (0);
}

/*Initialises 2d int fd arr for pipes. '-1' as there are always
  only as many fds as pipes needed. */
int	init_fd_arr(t_data *data)
{
	int j;

	j = 0;
	if (data->proc_nbr < 2)
		return (0);
	data->fd_arr = malloc (sizeof(int *) * (data->proc_nbr - 1));
	if (!data->fd_arr)
		return (1);
	while (j < data->proc_nbr -1)
	{
		data->fd_arr[j] = malloc (sizeof(int) * 2);
		if (!data->fd_arr[j])
		{
			free_2d_int_arr_rev(&data->fd_arr, j);
			return (1);
		}
		data->fd_arr[j][0] = 0;
		data->fd_arr[j][1] = 1;
		j++;
	}
	return (0);	
}
