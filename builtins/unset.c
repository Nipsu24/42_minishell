/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:53:35 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/13 12:51:46 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to remove a variable from the environment. If the variable is not
   found, return 0. If the variable is found, remove it from the environment,
   by shifting the array to the left. */
int	unset(t_data *data)
{
	int		i;
	int		k;
	int		m;
	char	**tmp;

	k = 0;
	m = 0;
	i = find_var(data->temp_env, data->proc[data->j].cmd[1]);
	if (i == len_array(data->temp_env))
		return (0);
	tmp = malloc(sizeof(char) * len_array(data->temp_env));
	if (!tmp)
		return (1);
	while (data->temp_env[m])
	{
		if (m != i)
			tmp[k++] = ft_strdup(data->temp_env[m]);
		m++;
	}
	tmp[k] = NULL;
	free_arr(&data->temp_env);
	data->temp_env = tmp;
	return (0);
}
