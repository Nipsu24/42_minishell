/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_proc_structs_c.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:54:54 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/06 11:14:31 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Helper function of alloc_proc_structs, counts needed amount of strings 
  for cmd array and redir array.*/
static void	count_arrays(t_data *data)
{
	while (data->i < data->num_tokens
		&& data->token_list[data->i].type != PIPE && data->tokens[data->i])
	{
		if (data->token_list[data->i].type == COMMAND)
			data->count_cmd++;
		if (data->token_list[data->i].type > COMMAND
			&& data->token_list[data->i].type <= RED_OP)
			data->count_other++;
		data->i++;
	}
}

/*Helper of alloc_proc_structs, allocates memory for redir array in
  a process.*/
static int	alloc_redir_array(t_data *data)
{
	data->proc[data->j].redir
		= malloc ((data->count_other + 1) * sizeof(char *));
	if (!data->proc[data->j].redir)
		return (1);
	return (0);
}

/*Allocates memory for the needed fds in each process.*/
static int	alloc_fds(t_data *data)
{
	int	i;

	i = 0;
	if (data->proc[data->j].fd_amount == 0)
	{
		data->proc[data->j].fd = NULL;
		return (0);
	}
	data->proc[data->j].fd
		= malloc (sizeof(int) * (data->proc[data->j].fd_amount));
	if (!data->proc[data->j].fd)
	{
		helper_alloc_fds(data);
		return (1);
	}
	while (i < (data->proc[data->j].fd_amount))
	{
		data->proc[data->j].fd[i] = -1;
		i++;
	}
	return (0);
}

/*Helper of alloc_proc_structs, needed for norm reasins.*/
static int	helper_alloc_proc_structs(t_data *data)
{
	data->proc[data->j].fd_amount = data->count_other / 2;
	if (alloc_fds(data))
		return (1);
	if (data->i < data->num_tokens
		&& data->token_list[data->i].type == PIPE)
	{
		data->i++;
		data->count_cmd = 0;
		data->count_other = 0;
	}
	return (0);
}

/*Allocates memory for cmd array, redir array and fd array in process
  structs. If no command or redirection in process line, arrays will be 
  initialised with 1 char string, which later will be set to null.*/
int	alloc_proc_structs(t_data *data)
{
	data->i = 0;
	data->count_cmd = 0;
	data->count_other = 0;
	while (data->j < data->proc_nbr)
	{
		count_arrays(data);
		if (data->count_cmd)
		{
			data->proc[data->j].cmd
				= malloc ((data->count_cmd + 1) * sizeof(char *));
			if (!data->proc[data->j].cmd)
				return (1);
		}
		else
			data->proc[data->j].cmd = NULL;
		if (data->count_other)
		{
			if (alloc_redir_array(data))
				return (1);
		}
		if (helper_alloc_proc_structs(data))
			return (1);
		data->j++;
	}
	return (0);
}
