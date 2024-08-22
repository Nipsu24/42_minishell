/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:04:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/22 13:46:45 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
	{
		printf("Error: No environment variables found\n");
		return ;
	}
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

int	export(t_data *data)
{
	int	i;

	if (!data || !data->proc || !data->proc[data->j].cmd)
	{
		data->exit_status = 1;
		perror("export command failed");
		return (data->exit_status);
	}
	i = len_array(data->proc[data->j].cmd);
	if (i > 2)
	{
		data->exit_status = 1;
		perror(data->proc[data->j].cmd[0]);
		return (data->exit_status);
	}
	if (i == 1)
	{
		print_export_env(data->temp_env);
		return (0);
	}
	else
		update_var(data, data->proc[data->j].cmd[1]);
	return (0);
}
