/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:36:01 by mmeier            #+#    #+#             */
/*   Updated: 2024/07/25 12:32:24 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Sets all token values to -1 in order to avoid garbage values when assigning
  these tokens to 2d array in ft_token_type function*/
static void	init_token_type(t_data *data, int num_tokens)
{
	int	i;

	i = 0;
	while (num_tokens > 0)
	{
		data->token_list[i].type = INIT_VAL;
		num_tokens--;
		i++;
	}
}

/*Allocates memory for t_token structs. Calculates first amount of 
  tokens available which is relevant for allocating right amount of t_token 
  structs.*/

int	ft_malloc_token(t_data *data)
{
	int	num_tokens;

	num_tokens = 0;
	while (data->tokens[num_tokens])
		num_tokens++;
	data->token_list = (t_token *) malloc(num_tokens * sizeof(t_token));
	if (!data->token_list)
		return (0);
	init_token_type(data, num_tokens);
	return (1);
}

/*Assigns type (e.g. 'pipe', 'command' etc.) to each identified token.*/
void	ft_token_type(t_data *data, int i)
{
	if (data->token_list[i].type < COMMAND || data->token_list[i].type > RED_OP)
		data->token_list[i].type = COMMAND;
	if (ft_strncmp(data->tokens[i], "<<", 2) == 0)
	{
		data->token_list[i].type = RED_OP;
		data->token_list[i + 1].type = HEREDOC;
	}
	else if (ft_strncmp(data->tokens[i], ">>", 2) == 0)
	{
		data->token_list[i].type = RED_OP;
		data->token_list[i + 1].type = REDIRECT_OUT_APP;
	}
	else if (ft_strncmp(data->tokens[i], "<", 1) == 0)
	{
		data->token_list[i].type = RED_OP;
		data->token_list[i + 1].type = REDIRECT_IN;
	}
	else if (ft_strncmp(data->tokens[i], ">", 1) == 0)
	{
		data->token_list[i].type = RED_OP;
		data->token_list[i + 1].type = REDIRECT_OUT;
	}
	else if (data->tokens[i][0] == '|'
		&& ft_strlen(data->tokens[i]) == 1)
		data->token_list[i].type = PIPE;
	else if (i > 0 && ((data->token_list[i - 1].type == REDIRECT_IN)
		|| (data->token_list[i - 1].type == REDIRECT_OUT)))
		data->token_list[i].type = COMMAND;
	else if (i > 0 && data->token_list[i - 1].type == PIPE)
		data->token_list[i].type = COMMAND;
	else if (i > 0 && data->token_list[i - 1].type == COMMAND)
		data->token_list[i].type = COMMAND;
}

/*Helper function of alloc_proc_structs, counts needed amount of strings for cmd array
  and redir array.*/
static void	count_arrays(t_data *data, int *i)
{
	while (data->token_list[*i].type != PIPE && data->tokens[*i])
	{
		if (data->token_list[*i].type == COMMAND)
			data->count_cmd++;
		if (data->token_list[*i].type > COMMAND && data->token_list[*i].type <= RED_OP)
			data->count_other++;
		(*i)++;
	}
}

/*Allocates memory for cmd array and redir array in process structs. If no
  command or redirection in process line, arrays will be initialised with
  1 char string, which later will be set to null.*/
static int	alloc_proc_structs(t_data *data)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	data->count_cmd = 0;
	data->count_other = 0;
	while (j < data->proc_nbr)
	{
		count_arrays(data, &i);
		data->proc[j].cmd = malloc ((data->count_cmd + 1) * sizeof(char *));
		if (!data->proc[j].cmd)
			return (1);
		data->proc[j].redir = malloc ((data->count_other + 1) * sizeof(char *));
		if (!data->proc[j].redir)
			return (1);
		if (data->token_list[i].type == PIPE)
		{
			i++;
			data->count_cmd = 0;
			data->count_other = 0;
		}
		j++;
	}
	return (0);
}

/*Helper function of fill_proc_structs, copies input from data->tokens array into
  data->proc arrays (cmd and redir)*/
static int	fill_data(t_data *data)
{
	if (data->token_list[data->i].type == COMMAND)
	{
		data->proc[data->j].cmd[data->k] = ft_strdup(data->tokens[data->i]);
		if (!data->proc[data->j].cmd[data->k])
			return (free_proc_arr_rev(data));
		data->k++;
	}
	if (data->token_list[data->i].type > COMMAND && data->token_list[data->i].type <= RED_OP)
	{
		data->proc[data->j].redir[data->l] = ft_strdup(data->tokens[data->i]);
		if (!data->proc[data->j].redir[data->l])
			return (free_proc_arr_rev(data));
		data->l++;
	}
	return (0);
}

static int	fill_proc_structs(t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->k = 0;
	data->l = 0;
	
	while (data->j < data->proc_nbr)
	{
		while (data->token_list[data->i].type != PIPE && data->tokens[data->i])
		{
			if (fill_data(data))
				return (1);
			data->i++;
		}
		data->proc[data->j].cmd[data->k] = NULL;
		data->proc[data->j].redir[data->l] = NULL;
		if (data->token_list[data->i].type == PIPE)
		{
			data->i++;
			data->k = 0;
			data->l = 0;
		}
		data->j++;
	}
	data->i = 0;
	data->j = 0;
	data->k = 0;
	while (data->j < data->proc_nbr)
	{
		printf("CMD STRUCT %d:\n", data->j);
		while (data->proc[data->j].cmd[data->i])
		{
			printf("%s\n", data->proc[data->j].cmd[data->i]);
			data->i++;
		}
		printf("RED STRUCT %d:\n", data->j);
		while (data->proc[data->j].redir[data->k])
		{
			printf("%s\n", data->proc[data->j].redir[data->k]);
			data->k++;
		}
		data->k = 0;
		data->i = 0;
		data->j++;
	}
	return (0);
}
	
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
