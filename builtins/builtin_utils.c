/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:21:17 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/22 11:50:46 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	find_var(char **env, char *word)
{
	int	i;
	int	j;

	i = 0;
	j = len_array(env);
	if (!env || !word || !j)
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
		new_env[i] = ft_strdup(data->temp_env[i]);
		if (!new_env[i])
			free_arr_rev(&new_env, i);
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
		free_arr_rev(&new_env, i);
	new_env[i + 1] = NULL;
	free_arr(&data->temp_env);
	data->temp_env = new_env;
	return (0);
}

int	update_var(t_data *data, char *var)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!data || !data->temp_env || !var)
		return (1);
	tmp = ft_split(var, '=');
	if (!tmp)
		return (1);
	i = find_var(data->temp_env, tmp[0]);
	if (i == len_array(data->temp_env))
		add_var(data, var);
	else
	{
		printf("Updating %s\n", var);
		free_str(&data->temp_env[i]);
		data->temp_env[i] = ft_strdup(var);
		if (!data->temp_env[i])
			return (1);
	}
	free_arr(&tmp);
	return (0);
}

const char	*get_env_var(t_data *data, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (data->temp_env[i])
	{
		if (ft_strncmp(data->temp_env[i], var, len) == 0)
		{
			return (data->temp_env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}
