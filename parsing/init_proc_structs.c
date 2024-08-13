/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_proc_structs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:28:18 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/13 14:42:13 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Counts amount of pipes of a command and allocates memory
  for sufficient amount of process-structs. If pipe amount
  is 0, one process struct will nevertheless be created.*/
static int	count_pipes(t_data *data)
{
	int	i;
	int	p_cnt;

	i = 0;
	p_cnt = 0;
	while (data->tokens[i])
	{
		if (data->token_list[i].type == PIPE)
			p_cnt++;
		i++;
	}
	data->proc = (t_prc *) malloc ((p_cnt + 1) * sizeof(t_prc));
	if (!data->proc)
		return (1);
	data->proc_nbr = p_cnt + 1;
	return (0);
}

/*Helper function of alloc_proc_structs, counts needed amount of strings 
  for cmd array and redir array.*/
static void	count_arrays(t_data *data)
{
	while (data->i < data->num_tokens && data->token_list[data->i].type != PIPE && data->tokens[data->i])
	{
		if (data->token_list[data->i].type == COMMAND)
			data->count_cmd++;
		if (data->token_list[data->i].type > COMMAND
			&& data->token_list[data->i].type <= RED_OP)
			data->count_other++;
		data->i++;
	}
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
		return (1);
	}
	while (i < (data->proc[data->j].fd_amount))
	{
		data->proc[data->j].fd[i] = -1;
		i++;
	}
	return (0);
}

/*Allocates memory for cmd array, redir array and fd array in process
  structs. If no command or redirection in process line, arrays will be 
  initialised with 1 char string, which later will be set to null.*/
static int	alloc_proc_structs(t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->count_cmd = 0;
	data->count_other = 0;
	while (data->j < data->proc_nbr)
	{
		count_arrays(data);
		data->proc[data->j].cmd
			= malloc ((data->count_cmd + 1) * sizeof(char *));
		if (!data->proc[data->j].cmd)
			return (1);
		data->proc[data->j].redir
			= malloc ((data->count_other + 1) * sizeof(char *));
		if (!data->proc[data->j].redir)
			return (1);
		data->proc[data->j].fd_amount = data->count_other / 2;
		if (alloc_fds(data))
			return (1);
		if (data->i < data->num_tokens && data->token_list[data->i].type == PIPE)
		{
			data->i++;
			data->count_cmd = 0;
			data->count_other = 0;
		}
		data->j++;
	}
	return (0);
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
			data->proc[data->j].redir[data->l] = ft_strdup(data->tokens[data->i]);
			if (!data->proc[data->j].redir[data->l])
				return (free_proc_arr_rev(data));
			data->l++;
		}
	}
	return (0);
}

/*Populates proc structs' string arrays (cmd and redir) with respective
  strings*/
static int	fill_proc_structs(t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->k = 0;
	data->l = 0;
	while (data->j < data->proc_nbr)
	{
		while (data->i < data->num_tokens && data->token_list[data->i].type != PIPE && data->tokens[data->i])
		{
			if (fill_data(data))
				return (1);
			data->i++;
		}
		data->proc[data->j].cmd[data->k] = NULL;
		data->proc[data->j].redir[data->l] = NULL;
		data->proc[data->j].path = NULL;
		data->proc[data->j].here_tmp = NULL;
		data->proc[data->j].here_name = NULL;
		if (data->i < data->num_tokens && data->token_list[data->i].type == PIPE)
		{
			data->i++;
			data->k = 0;
			data->l = 0;
		}
		data->j++;
	}
	return (0);
}
// 	data->i = 0; //for printing, if not needed anymore, remove until return (0)
// 	data->j = 0;
// 	data->k = 0;
// 	data->l = 0;
// 	while (data->j < data->proc_nbr)
// 	{
// 		printf("CMD ARRAY %d:\n", data->j);
// 		while (data->proc[data->j].cmd[data->i])
// 		{
// 			printf("%s\n", data->proc[data->j].cmd[data->i]);
// 			data->i++;
// 		}
// 		printf("RED ARRAY %d:\n", data->j);
// 		while (data->proc[data->j].redir[data->k])
// 		{
// 			printf("%s\n", data->proc[data->j].redir[data->k]);
// 			data->k++;
// 		}
// 		printf("FD ARRAY %d:\n", data->j);
// 		while (data->l < data->proc[data->j].fd_amount)
// 		{
// 			printf("%d\n", data->proc[data->j].fd[data->l]);
// 			data->l++;
// 		}
// 		data->k = 0;
// 		data->i = 0;
// 		data->l = 0;
// 		data->j++;
// 	}
// 	return (0);
// }

int	init_proc_structs(t_data *data)
{
	if (count_pipes(data))
		return (1);
	if (alloc_proc_structs(data))
		return (1);
	if (fill_proc_structs(data))
		return (1);
	return (0);
}
