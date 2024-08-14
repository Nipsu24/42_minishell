/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:21:17 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/14 14:52:59 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_var(char **env, char *word)
{
	int	i;
	int	j;

	i = 0;
	j = len_array(env);
	if (!env)
		return (0);
	while ((i < j) && ft_strncmp(word, env[i], ft_strlen(word)))
		i++;
	return (i);
}

int	add_var(t_data *data, char *var)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = len_array(data->temp_env);
	new_env = malloc(sizeof(char *) * (j + 2));
	if (!new_env)
		return (1);
	while (i < j)
	{
		new_env[i]
			= ft_substr(data->temp_env[i], 0, ft_strlen(data->temp_env[i]));
		if (!new_env[i])
			free_arr_rev(&new_env, i);
		i++;
	}
	new_env[i] = ft_substr(var, 0, ft_strlen(var));
	if (!new_env[i])
		free_arr_rev(&new_env, i);
	new_env[i + 1] = NULL;
	free_arr(&data->temp_env);
	data->temp_env = new_env;
	free_arr(&new_env);
	return (0);
}

int	update_var(t_data *data, char *var)
{
	int	i;

	i = find_var(data->temp_env, var);
	if (i == len_array(data->temp_env))
		return (add_var(data, var));
	free(data->temp_env[i]);
	data->temp_env[i] = ft_substr(var, 0, ft_strlen(var));
	if (!data->temp_env[i])
		return (1);
	free_str(&var);
	return (0);
}

int	len_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}
