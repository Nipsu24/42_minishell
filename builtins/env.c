/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:26:55 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/15 13:34:23 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Creates copy of env var in order to being able of modifying this copy
  later on in the course of the shell execution*/
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
		data->temp_env[i] = ft_substr(env[i], 0, ft_strlen(env[i]));
		if (!data->temp_env[i])
			return (free_arr_rev(&data->temp_env, i));
		i++;
	}
	update_shlvl(data);
	data->temp_env[i] = NULL;
	return (data->temp_env);
}

/*Prints the envrironmental variable*/
void	print_env(t_data *data)
{
	int	i;

	i = len_array(data->proc[data->j].cmd);
	if (!data || !(data->temp_env))
		return ;
	if (i > 1)
	{
		data->exit_status = 127;
		perror(data->proc[data->j].cmd[0]);
		free_str(&data->proc[data->j].cmd[0]);
		exit(data->exit_status);
	}
	while (data->temp_env[i])
	{
		if (ft_strchr(data->temp_env[i], '='))
		{
			if (ft_strncmp(data->temp_env[i], "_=", 2) == 0)
				printf("_=/usr/bin/env\n");
			else
				printf("%s\n", data->temp_env[i]);
		}
		i++;
	}
	free_str(&data->proc[data->j].cmd[0]);
}

int	update_shlvl(t_data *data)
{
	int		i;
	int		j;

	i = find_var(data->temp_env, "SHLVL=");
	if (i == len_array(data->temp_env))
	{
		add_var(data, "SHLVL=1");
		if (!data->temp_env)
			return (1);
	}
	else
	{
		j = ft_atoi(data->temp_env[i] + 6);
		j++;
		if (j > 9999 || j < 2)
			update_var(data, "SHLVL=1");
		free(data->temp_env[i]);
		data->temp_env[i] = ft_strjoin("SHLVL=", ft_itoa(j));
		if (!data->temp_env[i])
			return (1);
	}
	return (0);
}
