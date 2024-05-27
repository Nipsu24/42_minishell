/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:48:13 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/27 15:58:59 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_path(t_data *data)
{
	int	i;
	int j;
	int	found;

	i = 0;
	j = 0;
	found = 0;
	while (data->temp_env[i])
	{
		if (data->temp_env[i] && ft_strnstr(data->temp_env[i], "PATH=", ft_strlen(data->temp_env[i])))
		{
			data->path = ft_split(data->temp_env[i], ':');
			found = 1;
			if (!data->path)
				return (1);
		}
		i++;
	}
	while (data->path[j])
	{
		printf("%s\n", data->path[j]);
		j++;
	}
	if (found == 1)
		return (0);
	return (1);
}


int	ft_exec(t_data *data)
{
	if (split_path(data))
		return (1);
	return (0);
}