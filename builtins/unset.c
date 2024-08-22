/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:53:35 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/22 15:06:26 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_env(t_data *data)
{
	char	**new_env;
	int		i;
	
	new_env = malloc(sizeof(char) * (len_array(data->temp_env)));
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->temp_env)
	{
		new_env[i] = data->temp_env[i];
		i++;
	}
//	new_env[i] = NULL;
	return (new_env);
}

int	unset(t_data *data)
{
	int		i;
	char	**tmp;
	char	**new_env;

	tmp = ft_split(data->proc[data->j].cmd[1], '=');
	i = find_var(data->temp_env, tmp[0]);
	if (i == len_array(data->temp_env))
		return (0);
	while (i < len_array(data->temp_env))
	{
		data->temp_env[i] = data->temp_env[i + 1];
		i++;
	}
	data->temp_env[i] = NULL;
	free_arr(&tmp);
	new_env = copy_env(data);
	free_arr(&data->temp_env);
	data->temp_env = new_env;
	return (0);
}
