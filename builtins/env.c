/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:26:55 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/17 15:15:35 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Creates copy of env var in order to being able of modifying this copy
  later on in the course of the shell execution */
char	**ft_copy_env(char **env, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[j])
		j++;
	data->temp_env = (char **) malloc (sizeof(char *) * (j + 1));
	if (!data->temp_env)
		return (NULL);
	while (env[i])
	{
		data->temp_env[i] = NULL;
		data->temp_env[i] = ft_strdup(env[i]);
		if (!data->temp_env[i])
			return (free_arr_rev(&data->temp_env, i));
		i++;
	}
	data->temp_env[i] = NULL;
	update_shlvl(data);
	return (data->temp_env);
}

/* Prints the envrironmental variable. If there are arguments, return error.
   If there are no arguments, print the environment variables */
void	print_env(t_data *data)
{
	int	i;

	i = len_array(data->proc[data->j].cmd);
	if (!data || !(data->temp_env))
		return ;
	if (i != 1)
	{
		update_exit_status(data, 127, NULL, "Error: Too many arguments");
		free_str(data->proc[data->j].cmd);
		exit(data->exit_status);
	}
	i = 0;
	while (data->temp_env[i])
	{
		if (ft_strchr(data->temp_env[i], '='))
		{
			if (!ft_strncmp(data->temp_env[i], "_=", 2))
				printf("_=/usr/bin/env\n");
			else
				printf("%s\n", data->temp_env[i]);
		}
		i++;
	}
}

/* Function to update the shell level variable in the environment, if it is not
  set, it will be set to 0. If it is set, it will be incremented by 1. If the
  shell level is higher than 999, it will be reset to 1 */
int	update_shlvl(t_data *data)
{
	int	i;
	int	j;

	i = find_var(data->temp_env, "SHLVL");
	if (i == len_array(data->temp_env))
	{
		update_var(data, "SHLVL=0");
		return (0);
	}
	j = ft_atoi(data->temp_env[i] + 6);
	if (j > 999)
	{
		print_error("env",
			"Warning. Shell level too high (1000). Resetting to 1");
		update_var(data, "SHLVL=1");
	}
	else
	{
		j++;
		free_str(&data->temp_env[i]);
		data->temp_env[i] = ft_ms_strjoin_rev_free("SHLVL=", ft_itoa(j));
	}
	return (0);
}
