/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:48:13 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/28 16:12:59 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_path(t_data *data)
{
	int	i;
	//int j;
	int	found;

	i = 0;
	//j = 0;
	found = 0;
	while (data->temp_env[i])
	{
		if (data->temp_env[i] && ft_strnstr(data->temp_env[i], "PATH=", ft_strlen(data->temp_env[i])))
		{
			data->path = ft_split(data->temp_env[i], ':');
			found = 1;
			if (!data->path)
				return (1);
		}
		i++;
	}
	// while (data->path[j])
	// {
	// 	printf("%s\n", data->path[j]);
	// 	j++;
	// }
	if (found == 1)
		return (0);
	return (1);
}

/*If access() with F_OK returns 0 it indicates that the path is valid and the file can be
  accessed. */
static int	check_path_access(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->token_list->entry[i].cnt)
	{
		if (data->token_list->entry[i].type == COMMAND)
		{
			// printf("TEST3\n");
			// printf("%s", data->token_list->entry[i].cnt);
			while (data->path[j])
			{
				data->val_pth = ft_strjoin(data->path[j], data->token_list->entry[i].cnt);
				if (!data->val_pth)
					return (1);
				if ((access(data->val_pth, F_OK) == 0))
					return (0);
				else
				{
					free(data->val_pth);
					data->val_pth = NULL;
				}
				j++;
			}
		}
		i++;
	}
	return (1);
}

static int	ft_exec_cmd(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(data->val_pth, NULL, data->temp_env);
		// printf("TEST4");
	}
	return (0);
}

int	ft_exec(t_data *data)
{
	if (split_path(data))
		return (1);
	if (!check_path_access(data))
	{
		// printf("TEST2");
		ft_exec_cmd(data);
	}
	return (0);
}