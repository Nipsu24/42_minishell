/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:42:09 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/04 15:22:06 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*Initialises t_com_lst which holds all command structures which in turn are based 
//   on the amount of pipes encountered in the 2d array 'data->tokens'.
//   Counts amount of commants based on amount of pipes. Pipe count starts at 1 
//   as cmd structure also needs to be initiated if there are no pipes present 
//   in the user input*/
// static int	init_cmd_structs(t_data *data)
// {
// 	int	pipe_count;
// 	int	j;

// 	pipe_count = 1;
// 	j = 0;
// 	while (data->tokens[j])
// 	{
// 		if (data->tokens[j][0] == '|')
// 			pipe_count++;
// 		j++;
// 	}
// 	data->pipe_count = pipe_count;
// 	data->cmds = (t_com_lst *) malloc(sizeof(t_com_lst));
// 	if (!data->cmds)
// 		return (1);
// 	data->cmds->cmd = (t_command *) malloc(pipe_count * sizeof(t_command));
// 	if (!data->cmds->cmd)
// 		return (1);
// 	return (0);
// }

// /*Takes av_count (ARGUMENT count) from init_cmd_structs function and 
//   allocates memory for commands array. + 2 as it allocates also space
//   for 0-Terminator and command itself*/
// static int init_cmd_args(t_data *data, int av_count, int i, int pipe_check, int start)
// {
// 	int	j;
// 	int	k;

// 	j = start;
// 	k = 0;
// 	data->cmds->cmd[i].args = (char **) malloc ((sizeof(char *)) * (av_count + 2));
// 	if (!data->cmds->cmd[i].args)
// 		return (1);
// 	while (data->tokens[j] && j < pipe_check)
// 	{
// 		if (data->token_list->entry[j].type == COMMAND || data->token_list->entry[j].type == ARGUMENT)
// 		{
// 			data->cmds->cmd[i].args[k] = ft_strdup(data->token_list->entry[j].cnt);
// 			if (!data->cmds->cmd[i].args[k])
// 				return (1);
// 			k++;
// 		}
// 		j++;
// 	}
// 	data->cmds->cmd[i].args[k] = NULL;
// 	return (0);
// }

// static int	fill_cmd_structs(t_data *data)
// {
// 	int	j;
// 	int	i;
// 	int	av_count;
// 	int	pipe_check;
// 	int	start;

// 	j = 0;
// 	i = 0;
// 	av_count = 0;
// 	pipe_check = 0;
// 	start = 0;
// 	init_cmd_structs(data);
// 	while (data->pipe_count >= 1)
// 	{	
// 		data->cmds->cmd[i].file_out = NULL;
// 		data->cmds->cmd[i].file_in = NULL;
// 		start = j;
// 		while (data->tokens[j] && data->tokens[j][0] != '|')
// 		{
// 			if (data->token_list->entry[j].type == ARGUMENT)
// 				av_count++;
// 			if (data->token_list->entry[j].type == COMMAND)
// 				data->cmds->cmd[i].cnt = ft_strdup(data->token_list->entry[j].cnt);
// 			if (data->token_list->entry[j].type == REDIRECT_IN)
// 				data->cmds->cmd[i].file_in = ft_strdup(data->token_list->entry[j + 1].cnt);
// 			if (data->token_list->entry[j].type == REDIRECT_OUT)
// 				data->cmds->cmd[i].file_out = ft_strdup(data->token_list->entry[j + 1].cnt);
// 			j++;
// 		}
// 		if (data->tokens[j][0] == '|')
// 		{
// 			pipe_check = j;
// 			j++;
// 		}
// 		init_cmd_args(data, av_count, i, pipe_check, start);
// 		data->pipe_count--;
// 		i++;
// 	}
// 	return (0);
// }


static void	jump_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

void	redirect_in_token(char *str, int *i)
{
	int	start;

	(*i)++;
	if (str[*i] == ' ')
			jump_spaces(str, i);
	start = *i;
	while (str[*i] && str[*i] != ' ')
		(*i++);
	cmd_token_arr[0] = ft_substr(str, start, *i - start);
	cmd_token_arr[1] = NULL;
	cmd_token_enum = REDIRECT_OUT;
}


static int	parse_str(char *str)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			jump_spaces(str, &i);
		start = i;
		if (str[i] == '<' && str[i + 1] == '<')
			/*heredoc REDIRECT_IN_DEL*/
		else if (str[i] == '>' && str[i + 1] == '>')
			/*REDIRECT_OUT_APP*/
		else if (str[i] == '<' && str[i + 1] != '<')
			redirect_in_token(str, &i);
			
		
		i++;
	}
}

static int	fill_cmd_structs(t_data *data)
{
	int j;
	int	i;

	j = 0;
	i = 0;
	while (data->prcs[j])
	{
		parse_str(data->prcs[j]);
		j++;
	}
	return (0);
}

int		parse_cmds(t_data *data)
{
	fill_cmd_structs(data);
	return (0);
}