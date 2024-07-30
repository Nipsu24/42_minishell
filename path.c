/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:35:14 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/07/30 10:35:25 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Loops through env variable until "PATH=" is found. Is then splitting
  the directory paths of this env var into data->path_arr.*/
static int	create_path_arr(t_data *data)
{
	int	i;
	char *tmp;

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
	//int		i;

	j = 0;
	slash = "/";
	//i = -1;
	while (data->path_arr[j])
	{
		data->path_arr[j] = ft_gnl_strjoin(data->path_arr[j], slash);
		if (!data->path_arr[j])
			return (1);
		j++;
	}
	// printf("PATH ARRAY:\n");
	// while (++i, data->path_arr[i])
	// 	printf("%s\n", data->path_arr[i]);
	return (0);
}

int	init_path(t_data *data)
{
	if (create_path_arr(data))
		return (1);
	if (join_slash(data))
		return (1);
	return (0);
}
