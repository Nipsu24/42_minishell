/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:53:35 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/10 15:47:50 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to remove a variable from the environment. If the variable is not
   found, return 0. If the variable is found, remove it from the environment,
   by shifting the array to the left. */
int	unset(t_data *data)
{
	int		i;

	i = find_var(data->temp_env, data->proc[data->j].cmd[1]);
	if (i == len_array(data->temp_env))
		return (0);
	while (data->temp_env[i])
	{
		free_str(&data->temp_env[i]);
		data->temp_env[i] = data->temp_env[i + 1];
		i++;
	}
	return (0);
}
