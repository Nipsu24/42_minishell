/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:03:23 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/18 12:00:39 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mid(t_data *data, int exit_flag)
{
	if (data->err_flag)
		return ;
	if (data->input)
		free_str(&data->input);
	if (data->tokens && data->tokens[0])
		free_arr_void(&data->tokens);
	if (data->token_list)
	{
		free(data->token_list);
		data->token_list = NULL;
	}
	if (data->proc_nbr)
		free_proc_structs(data);
	if (data->path_arr)
		free_arr_void(&data->path_arr);
	if (data->pid_arr)
		free_int_arr(&data->pid_arr);
	if (data->fd_arr)
		free_2d_int_arr(data, &data->fd_arr);
	if (exit_flag)
		exit(data->exit_status);
}

/*Exit_flag 1: failure; Exit_flag 2: success.
  Frees relevant parts of the main struct.*/
void	free_all(t_data *data, int exit_flag)
{
	if (data->err_flag)
		return ;
	if (data->input)
		free_str(&data->input);
	if (data->tokens && data->tokens[0])
		free_arr_void(&data->tokens);
	if (data->token_list)
	{
		free(data->token_list);
		data->token_list = NULL;
	}
	if (data->proc_nbr)
		free_proc_structs(data);
	if (data->path_arr)
		free_arr_void(&data->path_arr);
	if (data->pid_arr)
		free_int_arr(&data->pid_arr);
	if (data->fd_arr)
		free_2d_int_arr(data, &data->fd_arr);
	if (data->temp_env)
		free_arr(&data->temp_env);
	if (exit_flag)
		exit(data->exit_status);
}

/*Helper function of free_proc_arrays_rev, loops through redir array.*/
static void	free_redir(t_data *data)
{
	while (data->l > 0)
	{
		free(data->proc[data->j].redir[data->l - 1]);
		data->l--;
	}
}

/*Helper function of free_proc_arr_rev*/
static void	free_rest_rev(t_data *data)
{
	if (data->proc[data->j].fd != NULL)
		free_int_arr(&data->proc[data->j].fd);
	if (data->proc[data->j].here_name != NULL)
		free_str(&data->proc[data->j].here_name);
	if (data->proc[data->j].here_tmp != NULL)
		free_str(&data->proc[data->j].here_tmp);
}

/*Frees proc arrays in case of failed memory allocation for either cmd or
  redir arrays*/
int	free_proc_arr_rev(t_data *data)
{
	while (data->j >= 0)
	{
		if (data->proc[data->j].cmd != NULL)
		{
			while (data->k > 0)
			{
				free(data->proc[data->j].cmd[data->k - 1]);
				data->k--;
			}
			free(data->proc[data->j].cmd);
			data->proc[data->j].cmd = NULL;
		}
		if (data->proc[data->j].redir != NULL)
		{
			free_redir(data);
			free(data->proc[data->j].redir);
			data->proc[data->j].redir = NULL;
		}
		free_rest_rev(data);
		data->j--;
	}
	free(data->proc);
	data->proc = NULL;
	return (1);
}
