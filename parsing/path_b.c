/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:35:14 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/09/06 11:02:45 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Helper function of join_cmd_path, joins cmd[0] to path arr strings
  and checks if path is valid and returns -1 for breaking out of loop.
  In case cmd[0] start with either '.' or '/' (indicating it's a path
  itself) cmd[0] gets duplicated into path var of respective process.*/
static int	join_cmd_path_loop(t_data *data)
{
	if (data->path_arr[data->i]
		&& data->proc[data->j].cmd[0][0] != '.'
		&& data->proc[data->j].cmd[0][0] != '/')
		data->proc[data->j].path
			= ft_strjoin(data->path_arr[data->i],
				data->proc[data->j].cmd[0]);
	else
		data->proc[data->j].path
			= ft_strdup(data->proc[data->j].cmd[0]);
	if (!data->proc[data->j].path)
		return (1);
	if (access(data->proc[data->j].path, F_OK) == 0)
		return (-1);
	free(data->proc[data->j].path);
	data->proc[data->j].path = NULL;
	return (0);
}

/*Loops through the path_arr array and joins the command of each process
  with each string in the path array into the *path variable. In case the 
  path exists, breaks out of path_arr while loop and continues with next
  process (if available). In case the command cannot be found 
  (via access function) the path string remains empty (NULL). */
int	join_cmd_path(t_data *data)
{
	int	return_val;

	return_val = 0;
	data->j = 0;
	data->i = 0;
	while (data->j < data->proc_nbr)
	{
		data->i = 0;
		if (data->proc[data->j].cmd != NULL)
		{
			while (data->path_arr[data->i])
			{
				return_val = join_cmd_path_loop(data);
				if (return_val == -1)
					break ;
				if (return_val == 1)
					return (1);
				data->i++;
			}
		}
		data->j++;
	}
	return (0);
}
