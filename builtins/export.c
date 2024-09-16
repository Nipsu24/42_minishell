/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:04:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/16 12:41:22 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to print the environment variables. If there are no variables, print
   an error message. If there are variables, print them with the format
   "declare -x VARIABLE". */
static void	print_export_env(char **env)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!env)
	{
		print_error("export", "No environment variables found");
		return ;
	}
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		printf("declare -x %s=\"%s\"\n", tmp[0], tmp[1]);
		i++;
		free_arr(&tmp);
	}
}

/* Function to check if a string is alphanumeric. If the string is
alphanumeric, return true. If the string is not alphanumeric, return false. */
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

/* Function to check if the variable to be exported is valid. If the variable
   is not valid, print an error message and return false. If the variable is
   valid, return true. */
static bool	valid_export(t_data *data, char *var)
{
	char	**tmp;

	tmp = ft_split(var, '=');
	if (!tmp || !tmp[0])
		return (free_arr(&tmp), update_exit_status(data, 1, "export",
				"Not a valid identifier"), false);
	if (!is_str_alpha(tmp[0]))
		return (free_arr(&tmp), update_exit_status(data, 1, "export",
				"Not a valid identifier"), false);
	if (tmp[1] && is_str_alpha(tmp[0]))
		return (free_arr(&tmp), true);
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
	if (i == 1)
	{
		print_export_env(data->temp_env);
		return (0);
	}
	else
	{
		i = 0;
		while (i++, data->proc[data->j].cmd[i])
		{
			if (valid_export(data, data->proc[data->j].cmd[i]))
				update_var(data, data->proc[data->j].cmd[i]);
		}
	}
	return (0);
}
