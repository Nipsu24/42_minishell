/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:03:23 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/14 14:06:38 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Exit_flag 1: failure; Exit_flag 2: success.
  Frees relevant parts of the main struct.*/
void	free_all(t_data *data, int exit_flag)
{
	int	j;

	j = 0;
	if (data->input)
		free_str(&data->input);
	if (data->tokens && data->tokens[j])
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
	if (exit_flag == 1)
		exit(EXIT_FAILURE);
	if (exit_flag == 2)
		exit(EXIT_SUCCESS);
	return ;
}

/*Frees all proc_structs in order.*/
void	free_proc_structs(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->proc_nbr)
	{
		if (data->proc[j].cmd != NULL)
			free_arr_void(&data->proc[j].cmd);
		if (data->proc[j].redir != NULL)
			free_arr_void(&data->proc[j].redir);
		if (data->proc[j].path != NULL)
			free_str(&data->proc[j].path);
		if (data->proc[j].fd != NULL)
			free_int_arr(&data->proc[j].fd);
		if (data->proc[j].here_tmp != NULL)
			free_str(&data->proc[j].here_tmp);
		if (data->proc[j].here_name != NULL)
			free_str(&data->proc[j].here_name);
		j++;
	}
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
		if (data->proc[data->j].fd != NULL)
			free_int_arr(&data->proc[data->j].fd);
		if (data->proc[data->j].here_name != NULL)
			free_str(&data->proc[data->j].here_name);
		if (data->proc[data->j].here_tmp != NULL)
			free_str(&data->proc[data->j].here_tmp);
		data->j--;
	}
	return (1);
}
