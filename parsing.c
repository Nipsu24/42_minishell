/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:42:09 by mmeier            #+#    #+#             */
/*   Updated: 2024/06/03 16:24:34 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Counts amount of arguments between pipes based on current index*/
static int	count_args(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->tokens[i + j] && data->tokens[i + j][0] != '|')
		j++;
	return (i);
}

static int	fill_cmd_lst(t_data *data)
{
	int	i;
	int	j;
	int	args_nbr;
	t_command *head = NULL;
	t_command *current = NULL;

	i = 0;
	j = 0;
	args_nbr = 0;
	while (data->token_list->num >= 0)
	{
		if (data->token_list->entry[i].type == PIPE || data->token_list->entry[i].type == FILE_NAME)
		{
			i++;
			data->token_list->num--;
		}
		else if (data->token_list->entry[i].type == COMMAND)
		{
			data->cmds = malloc(sizeof(t_command));
			if (!(data->cmds))
				return (1);
			data->cmds->cmd = ft_strdup(data->tokens[i]);
			if (!(data->cmds->cmd))
				return (1);
			args_nbr = count_args(data, i);
			data->cmds->args = malloc(sizeof(char *) * (args_nbr + 1));
			data->cmds->file_in = NULL;
			data->cmds->file_in = NULL;
			data->cmds->next = NULL;
			while (j <= args_nbr)
			{
				data->cmds->args[j] = ft_strdup(data->tokens[j]);
				if (!data->cmds->args[j])
					return (1);
				j++;
			}
			data->cmds->args[args_nbr] = '\0';
			if (head == NULL)
				head == data->cmds;
			else
				current->next = data->cmds;
			current = data->cmds;
		}
		else if (data->token_list->entry[i].type == REDIRECT_IN)
			data->cmds->file_in = ft_strdup(data->tokens[i + 1]);
		else if (data->token_list->entry[i].type == REDIRECT_OUT)
			data->cmds->file_out = ft_strdup(data->tokens[i + 1]);
		i++;
		data->token_list->num--;
	}
	return (0);
}


int		parse_cmds(t_data *data)
{
	//t_commmand *cmd;
	data->cmds = NULL;
	fill_cmd_lst(data);
	return (0);
}