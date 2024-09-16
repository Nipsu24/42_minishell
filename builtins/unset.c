/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:53:35 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/16 16:11:47 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to eliminate the variable from the enviroment. If the variable is
found, remove it from the environment, by shifting the array to the left.*/
static void	do_unset(t_data *data, int i)
{
	char	**tmp;
	int		k;
	int		m;

	k = 0;
	m = 0;
	tmp = malloc(sizeof(char *) * len_array(data->temp_env));
	if (!tmp)
		return ;
	while (data->temp_env[m])
	{
		if (m != i)
			tmp[k++] = ft_strdup(data->temp_env[m]);
		m++;
	}
	tmp[k] = NULL;
	free_arr(&data->temp_env);
	data->temp_env = tmp;
}

/* Function to remove a variable from the environment. If the variable is not
   found, return 0. */
int	unset(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (j++, data->proc[data->j].cmd[j])
	{
		i = find_var(data->temp_env, data->proc[data->j].cmd[j]);
		if (i != len_array(data->temp_env))
			do_unset(data, i);
	}
	return (0);
}