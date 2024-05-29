/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:48:13 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/29 15:24:03 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!!Issue with splitting, data gets for some reason written into data->token_list->entry[k].cnt!!*/
static int	split_path(t_data *data)
{
	int	i;
	//int	k;
	int j;
	int	found;

	i = 0;
	//k = 0;
	j = 0;
	found = 0;
	data->path = NULL;
	while (data->temp_env[i])
	{
		if (data->temp_env[i] && ft_strnstr(data->temp_env[i], "PATH=", ft_strlen(data->temp_env[i])))
		{
			data->path = ft_split(data->temp_env[i], ':');
			if (!data->path)
				return (1);
			found = 1;
		}
		i++;
	}
	while (data->path[j])
	{
		printf("%s\n", data->path[j]);
		j++;
	}
	/*testing which input entry[k] holds, for some reason it contains now content from paths*/
	// while ((data->token_list->entry[k].cnt))
	// {
	// 	printf("%s\n", data->token_list->entry[k].cnt);
	// 	printf("TEST6\n");
	// 	k++;
	// }
	if (found == 1)
		return (0);
	return (1);
}

/*If access() with F_OK returns 0 it indicates that the path is valid and the file can be
  accessed.*/
static int	check_path_access(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	char *slash = "/";
	while (data->token_list->entry[i].cnt)
	{
		//printf("%s\n", data->token_list->entry[i].cnt);
		if (data->token_list->entry[i].type == COMMAND)
		{
			while (data->path[j])
			{
				data->val_pth = ft_strjoin(data->path[j], slash);
				if (!data->val_pth)
					return (1);
				data->val_pth = ft_strjoin(data->val_pth, data->token_list->entry[i].cnt);
				if (!data->val_pth)
					return (1);
				if ((access(data->val_pth, F_OK) == 0))
					return (0);
				else
				{
					//printf("minishell: %s: command not found\n", data->token_list->entry[i].cnt);
					free(data->val_pth);
					data->val_pth = NULL;
				}
				j++;
			}
			//printf("minishell: %s: command not found\n", data->token_list->entry[i].cnt);
		}
		i++;
	}
	//printf("minishell: %s: command not found\n", data->token_list->entry[k].cnt);
	return (1);
}

/*Line 107: Example on how the format of argv should be in order to use in in execve function*/
static int	ft_exec_cmd(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(data->val_pth, argv, data->temp_env);
		// echo /Users/mmeier "/Users/mmeier" '$HOME'
		argv = {"echo", "/Users/mmeier", "/Users/mmeier", "$HOME", NULL};
		typedef char ** t_command
		t_command *commands;
	}
	return (0);
}

int	ft_exec(t_data *data)
{	
	// int	k;

	// k = 0;
	// while ((data->token_list->entry[k].cnt))
	// {
	// 	printf("%s\n", data->token_list->entry[k].cnt);
	// 	printf("TEST6\n");
	// 	k++;
	// }
	if (split_path(data))
		return (1);
	if (!check_path_access(data))
	{
		// printf("PATH Directory of the command\n");
		// printf("%s\n", data->val_pth);
		ft_exec_cmd(data);
	}
	return (0);
}
