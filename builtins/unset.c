/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:53:35 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/23 16:20:09 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
