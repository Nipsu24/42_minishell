/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:36:01 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/20 12:10:52 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Sets all token values to -1 in order to avoid garbage values when assigning
  these tokens to 2d array in ft_token_type function*/
static void	init_token_type(t_data *data, int num_tokens)
{
	int	i;

	i = 0;
	while (i < num_tokens)
	{
		data->token_list[i].type = INIT_VAL;
		i++;
	}
}

/*Allocates memory for t_token structs. Calculates first amount of 
  tokens available which is relevant for allocating right amount of t_token 
  structs.*/

int	ft_malloc_token(t_data *data)
{
	data->num_tokens = 0;
	
	if (data->tokens && data->tokens[0] && data->tokens[0][0] == '\0')
		data->num_tokens++;
	else
	{
		while (data->tokens[data->num_tokens])
			data->num_tokens++;
		if (data->num_tokens == 0)
			return (0);
	}
	data->token_list = (t_token *) malloc(data->num_tokens * sizeof(t_token));
	if (!data->token_list)
		return (0);
	init_token_type(data, data->num_tokens);
	return (1);
}

/*2nd part of assign_token_type function*/
static void	assign_token_type_2(t_data *data, int i)
{
	if (data->tokens[i][0] == '|'
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

/*Assigns type (e.g. 'pipe', 'command' etc.) to each identified token.*/
void	assign_token_type(t_data *data, int i)
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
	else
		assign_token_type_2(data, i);
}
