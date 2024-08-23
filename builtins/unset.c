/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:53:35 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/23 22:04:03 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to remove a variable from the environment. If the variable is not
   found, return 0. If the variable is found, remove it from the environment,
   by shifting the array to the left. */
int	unset(t_data *data)
{
	int		i;
	char	**tmp;

	tmp = ft_split(data->proc[data->j].cmd[1], '=');
	if (!tmp)
		return (1);
	i = find_var(data->temp_env, tmp[0]);
	if (i == len_array(data->temp_env))
	{
		free_arr(&tmp);
		return (0);
	}
	while (data->temp_env[i + 1])
	{
		data->temp_env[i] = data->temp_env[i + 1];
		i++;
	}
	free(data->temp_env[i]);
	data->temp_env[i] = NULL;
	free_arr(&tmp);
	return (0);
}
