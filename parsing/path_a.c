/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:35:14 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/09/13 12:48:35 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks for path in env variables. If no path present, returns 1
  and init_path function quits directly.*/
static int	path_unset(t_data *data)
{
	int	i;

	i = 0;
	while (data->temp_env[i])
	{
		if (data->temp_env[i]
			&& ft_strnstr(data->temp_env[i], "PATH=", 5))
			return (0);
		i++;
	}
	return (1);
}

/*Checks if any of the cmd arrays is populated with data.
  If not, returns 1 and init_path function quits directly.*/
static int	check_for_cmds(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->proc_nbr)
	{
		if (data->proc[j].cmd != NULL)
			return (0);
		j++;
	}
	return (1);
}

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
			break ;
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
		data->path_arr[j] = ft_ms_strjoin(data->path_arr[j], slash);
		if (!data->path_arr[j])
			return (1);
		j++;
	}
	return (0);
}

/*Joins the path_arr with the cmd array to create a full path. If the
  path is found, the function returns 0 and the path is stored in
  data->proc[data->j].path.*/
int	init_path(t_data *data)
{
	if (path_unset(data))
		return (0);
	if (check_for_cmds(data))
		return (0);
	if (create_path_arr(data))
		return (1);
	if (join_slash(data))
		return (1);
	if (join_cmd_path(data))
		return (1);
	return (0);
}
