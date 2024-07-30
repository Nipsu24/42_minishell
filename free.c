/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:03:23 by mmeier            #+#    #+#             */
/*   Updated: 2024/07/29 11:50:57 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees relevant parts of the main struct.*/
void	free_all(t_data *data)
{
	int	j;

	j = 0;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens && data->tokens[j])
		free_arr_void(data->tokens);
	if (data->token_list)
	{
		free(data->token_list);
		data->token_list = NULL;
	}
	if (data->proc_nbr)
		free_proc_structs(data);
}

/*Frees 2d array in reversed order e.g. for failed copy
  of env variable in ft_copy_env function*/
char	**free_arr_rev(char **av, int i)
{
	if (av[i] == NULL || av == NULL)
		return (NULL);
	while (i > 0)
	{
		free(av[i - 1]);
		av[i - 1] = NULL;
		i--;
	}
	free(av);
	av = NULL;
	return (NULL);
}

/*Frees 2d array - char version*/
char	**free_arr(char **arr)
{
	int	j;

	j = 0;
	if (arr && arr[j])
	{
		while (arr[j])
		{
			free(arr[j]);
			arr[j] = NULL;
			j++;
		}
		free(arr);
		arr = NULL;
	}
	return (NULL);
}

/*Void version of free_arr*/
void	free_arr_void(char **arr)
{
	int	j;

	j = 0;
	if (arr && arr[j])
	{
		while (arr[j])
		{
			free(arr[j]);
			arr[j] = NULL;
			j++;
		}
		free(arr);
		arr = NULL;
	}
}

/*Frees string and sets pointer to NULL. Caller function
  should pass address of str to this function.*/
void	free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

/*Frees all proc_structs in order.*/
void	free_proc_structs(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->proc_nbr)
	{
		if (data->proc[j].cmd[0] != NULL
		|| data->proc[j].cmd != NULL)
			free_arr_void(data->proc[j].cmd);
		if (data->proc[j].redir[0] != NULL
		|| data->proc[j].redir != NULL)
			free_arr_void(data->proc[j].redir);
		if (data->proc[j].path != NULL)
			free_str(&data->proc[j].path);
		j++;
	}
}

/*Helper function of free_proc_arrays_rev, loops through redir array.*/
static void	free_redir(t_data *data)
{
	while (data->proc[data->j].redir[data->l] > 0)
	{
		free(data->proc[data->j].redir[data->l - 1]);
		data->l--;
	}
}

/*Frees proc arrays in case of failed memory allocation for either cmd or
  redir arrays*/
int	free_proc_arr_rev(t_data *data)
{
	while (data->j >= 0)
	{
		if (data->proc[data->j].cmd[data->k] != NULL
			|| data->proc[data->j].cmd != NULL)
		{
			while (data->proc[data->j].cmd[data->k] > 0)
			{
				free(data->proc[data->j].cmd[data->k - 1]);
				data->k--;
			}
			free(data->proc[data->j].cmd);
			data->proc[data->j].cmd = NULL;
		}
		if (data->proc[data->j].redir[data->l] != NULL
			|| data->proc[data->j].redir != NULL)
		{
			free_redir(data);
			free(data->proc[data->j].redir);
			data->proc[data->j].redir = NULL;
		}
		data->j--;
	}
	return (1);
}
