/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:35:14 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/07/31 10:23:48 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Loops through env variable until "PATH=" is found. Is then splitting
  the directory paths of this env var into data->path_arr.*/
static int	create_path_arr(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (data->temp_env[i])
	{
		if (data->temp_env[i]
			&& ft_strnstr(data->temp_env[i], "PATH=", 5))
		{
			data->path_arr = ft_split(data->temp_env[i], ':');
			if (!data->path_arr)
				return (1);
		}
		i++;
	}
	tmp = ft_strtrim(data->path_arr[0], "PATH=");
	if (!tmp)
		return (1);
	free(data->path_arr[0]);
	data->path_arr[0] = NULL;
	data->path_arr[0] = tmp;
	return (0);
}

/*Adds a '/' behind each string of the data->path_arr*/
static int	join_slash(t_data *data)
{
	int		j;
	char	*slash;

	j = 0;
	slash = "/";
	while (data->path_arr[j])
	{
		data->path_arr[j] = ft_gnl_strjoin(data->path_arr[j], slash);
		if (!data->path_arr[j])
			return (1);
		j++;
	}
	return (0);
}

/*Loops through the path_arr array and joins the command of each process
  with each string in the path array into the *path variable. In case the 
  path exists, breaks out of path_arr while loop and continues with next
  process (if available). In case the command cannot be found 
  (via access function) the path string remains empty (NULL). */
static int	join_cmd_path(t_data *data)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (j < data->proc_nbr)
	{
		i = 0;
		while (data->path_arr[i])
		{
			data->proc[j].path = ft_strjoin(data->path_arr[i],
					data->proc[j].cmd[0]);
			if (!data->proc[j].path)
				return (1);
			if (access(data->proc[j].path, F_OK) == 0)
				break ;
			free(data->proc[j].path);
			data->proc[j].path = NULL;
			i++;
		}
		//printf("PATH EXISTS: %s\n", data->proc[j].path);
		j++;
	}
	return (0);
}

int	init_path(t_data *data)
{
	if (create_path_arr(data))
		return (1);
	if (join_slash(data))
		return (1);
	if (join_cmd_path(data))
		return (1);
	return (0);
}
