/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:53:35 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/22 11:48:34 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_data *data)
{
	int		i;
	char	**tmp;

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
	return (0);
}
