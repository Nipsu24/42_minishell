/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_proc_structs_b.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:44:37 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/17 16:49:35 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Counts amount of pipes of a command and allocates memory
  for sufficient amount of process-structs. If pipe amount
  is 0, one process struct will nevertheless be created.*/
int	count_pipes(t_data *data)
{
	int	i;
	int	p_cnt;

	i = 0;
	p_cnt = 0;
	while (data->tokens[i] && i < data->num_tokens)
	{
		if (data->token_list[i].type == PIPE)
			p_cnt++;
		i++;
	}
	if (p_cnt > 255)
	{
		print_error("Error", "Too many pipes in command line :(");
		data->err_flag = 1;
		return (0);
	}
	data->proc = (t_prc *) malloc ((p_cnt + 1) * sizeof(t_prc));
	if (!data->proc)
		return (1);
	data->proc_nbr = p_cnt + 1;
	return (0);
}

/*Helper function of alloc_fds, frees cmd and redir arrays
  in case malloc fails for fds.*/
void	helper_alloc_fds(t_data *data)
{
	if (data->proc[data->j].cmd)
	{
		free(data->proc[data->j].cmd);
		data->proc[data->j].cmd = NULL;
	}
	if (data->proc[data->j].redir)
	{
		free(data->proc[data->j].redir);
		data->proc[data->j].redir = NULL;
	}
}

/*Helper function of fill_proc_structs, copies input from 
  data->tokens array into data->proc arrays (cmd and redir)*/
static int	fill_data(t_data *data)
{
	if (data->token_list[data->i].type == COMMAND)
	{
		data->proc[data->j].cmd[data->k] = ft_strdup(data->tokens[data->i]);
		if (!data->proc[data->j].cmd[data->k])
			return (free_proc_arr_rev(data));
		data->k++;
	}
	if (data->token_list[data->i].type > COMMAND
		&& data->token_list[data->i].type <= RED_OP)
	{
		if (data->tokens[data->i])
		{
			data->proc[data->j].redir[data->l]
				= ft_strdup(data->tokens[data->i]);
			if (!data->proc[data->j].redir[data->l])
				return (free_proc_arr_rev(data));
			data->l++;
		}
	}
	return (0);
}

/*further helper of fill_proc_structs, needed for norm reasons*/
static void	helper_fill_proc_structs(t_data *data)
{
	data->proc[data->j].path = NULL;
	data->proc[data->j].here_tmp = NULL;
	data->proc[data->j].here_name = NULL;
	if (data->i < data->num_tokens && data->token_list[data->i].type == PIPE)
	{
		data->i++;
		data->k = 0;
		data->l = 0;
	}
}

/*Populates proc structs' string arrays (cmd and redir) with respective
  strings*/
int	fill_proc_structs(t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->k = 0;
	data->l = 0;
	while (data->j < data->proc_nbr)
	{
		while (data->i < data->num_tokens && data->token_list[data->i].type
			!= PIPE && data->tokens[data->i])
		{
			if (fill_data(data))
				return (1);
			data->i++;
		}
		if (data->k)
			data->proc[data->j].cmd[data->k] = NULL;
		else
			data->proc[data->j].cmd = NULL;
		if (data->l)
			data->proc[data->j].redir[data->l] = NULL;
		else
			data->proc[data->j].redir = NULL;
		helper_fill_proc_structs(data);
		data->j++;
	}
	return (0);
}
