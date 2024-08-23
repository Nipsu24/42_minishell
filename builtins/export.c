/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:04:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/23 22:03:34 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to print the environment variables. If there are no variables, print
   an error message. If there are variables, print them with the format
   "declare -x VARIABLE". */
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

/* Function to update a variable in the environment. If the variable is not
found, add it to the environment. If the variable is found, update it. */
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
