/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:04:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/05 22:38:24 by cesasanc         ###   ########.fr       */
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
		print_error("export", "No environment variables found");
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
		update_exit_status(data, 1, "Error", "export command not found");
		return (data->exit_status);
	}
	i = len_array(data->proc[data->j].cmd);
	if (i > 2)
	{
		update_exit_status(data, 1, "Error", "Too many arguments");
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
