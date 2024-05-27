/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:36:01 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/23 14:59:58 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Allocates memory for t_tokens & t_token structs. Calculates first amount of 
  tokens available which is relevant for allocating right amount of t_token 
  structs.*/
int	ft_malloc_token(t_data *data)
{
	int	num_tokens;

	num_tokens = 0;
	while (data->tokens[num_tokens])
		num_tokens++;
	data->token_list = (t_tokens *) malloc(sizeof(t_tokens));
	if (!data->token_list)
		return (0);
	data->token_list->entry = (t_token *) malloc(num_tokens * sizeof(t_token));
	if (!data->token_list->entry)
		return (0);
	return (1);
}

/*Assigns type (e.g. 'pipe', 'command' etc.) to each identified token. Not all
  yet functional and recognised, needs rework.*/
void	ft_token_type(t_data *data, int i)
{
	if (data->token_list->entry[i].cnt[0] == '"')
		data->token_list->entry[i].type = STRING;
	else if (ft_strncmp(data->token_list->entry[i].cnt, "<<", 2) == 0)
		data->token_list->entry[i].type = REDIRECT_IN_DEL;
	else if (ft_strncmp(data->token_list->entry[i].cnt, ">>", 2) == 0)
		data->token_list->entry[i].type = REDIRECT_OUT_APP;
	else if (ft_strncmp(data->token_list->entry[i].cnt, "<", 1) == 0)
		data->token_list->entry[i].type = REDIRECT_IN;
	else if (ft_strncmp(data->token_list->entry[i].cnt, ">", 1) == 0)
		data->token_list->entry[i].type = REDIRECT_OUT;
	else if (data->token_list->entry[i].cnt[0] == '|'
		&& ft_strlen(data->token_list->entry[i].cnt) == 1)
		data->token_list->entry[i].type = PIPE;
	else if (i > 0 && ((data->token_list->entry[i - 1].cnt[0] == '<')
			|| (data->token_list->entry[i - 1].cnt[0] == '>')))
		data->token_list->entry[i].type = FILE_NAME;
	else if (data->token_list->entry[i].cnt[0] == '$')
		data->token_list->entry[i].type = ENVAR;
	else if (i > 2 && ((data->token_list->entry[i - 2].type == REDIRECT_IN)
			|| (data->token_list->entry[i - 2].type == REDIRECT_OUT))
		&& data->token_list->entry[i -1].type == FILE_NAME)
		data->token_list->entry[i].type = COMMAND;
	else
		data->token_list->entry[i].type = COMMAND;
}

/*Handles basic syntax errors e.g. if two PIPE-Tokens are next to each other or 
  if there is not input after a redirect arrow*/
int	token_syntax_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->token_list->entry[i].cnt)
	{
		if (i > 0 && data->token_list->entry[i - 1].type == PIPE
			&& data->token_list->entry[i].type == PIPE)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			return (1);
		}
		if ((data->token_list->entry[i].type == REDIRECT_IN
				|| data->token_list->entry[i].type == REDIRECT_OUT)
			&& (!(data->token_list->entry[i + 1].type)))
		{
			printf("minishell: syntax error near unexpected token 'newline'\n");
			return (1);
		}
		i++;
	}
	return (0);
}