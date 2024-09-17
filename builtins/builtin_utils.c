/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:21:17 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/17 15:20:18 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to find the length of a 2d array */
int	len_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

/* Function to find the index of a variable in the environment */
int	find_var(char **env, char *word)
{
	int		i;
	int		j;
	char	*tmp;

	if (!env || !word)
		return (-1);
	i = 0;
	j = len_array(env);
	tmp = ft_strjoin(word, "=");
	if (!tmp)
		return (0);
	while (i < j)
	{
		if (!ft_strncmp(tmp, env[i], ft_strlen(tmp)))
		{
			free(tmp);
			return (i);
		}
		i++;
	}
	free(tmp);
	return (i);
}

/* Function to add a variable to the environment, by creating a new array 
   and copying the old one into it */
int	add_var(t_data *data, char *var)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (len_array(data->temp_env) + 2));
	if (!new_env)
		return (1);
	while (i < len_array(data->temp_env))
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

/* Function to update a variable in the environment, by finding the variable
   and replacing it with the new value */
int	update_var(t_data *data, char *var)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!data || !data->temp_env || !var)
		return (1);
	tmp = ft_split(var, '=');
	if (!tmp || !tmp[0])
		return (1);
	i = find_var(data->temp_env, tmp[0]);
	if (i == len_array(data->temp_env))
		add_var(data, var);
	else
	{
		free_str(&data->temp_env[i]);
		data->temp_env[i] = ft_strdup(var);
		if (!data->temp_env[i])
			return (1);
	}
	free_arr(&tmp);
	return (0);
}

/* Function to get the value of an environment variable, by finding the variable
   and returning the value */
char	*get_env_var(t_data *data, char *var)
{
	int	i;
	int	len;

	i = 0;
	if (!data->temp_env || !var)
		return (NULL);
	len = ft_strlen(var);
	while (data->temp_env[i])
	{
		if (ft_strncmp(data->temp_env[i], var, len) == 0
			&& data->temp_env[i][len] == '=')
		{
			return (data->temp_env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}
