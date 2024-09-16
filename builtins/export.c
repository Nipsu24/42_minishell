/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:04:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/16 15:49:20 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to print the environment variables. If there are no variables, print
   an error message. If there are variables, print them with the format
   "declare -x VARIABLE". */
static void	print_export_env(char **env)
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

static bool	is_str_alpha(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (false);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static bool	valid_export(t_data *data, char *var)
{
	char	**tmp;

	tmp = ft_split(var, '=');
	if (!tmp || !tmp[0])
		return (update_exit_status(data, 1, NULL,
				"not a valid identifier"), false);
	if (!is_str_alpha(tmp[0]))
		return (update_exit_status(data, 1, NULL,
				"not a valid identifier"), false);
	if (tmp[1] && is_str_alpha(tmp[0]))
		return (true);
	free_arr(&tmp);
	return (false);
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
		update_exit_status(data, 0, "Error", "too many arguments");
		return (data->exit_status);
	}
	if (i == 1)
	{
		print_export_env(data->temp_env);
		return (0);
	}
	else
		if (valid_export(data, data->proc[data->j].cmd[1]))
			update_var(data, data->proc[data->j].cmd[1]);
	return (0);
}
