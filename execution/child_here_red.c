/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_here_red.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:00:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/29 15:17:30 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Handles redirection of heredoc content.*/
int	heredoc_exec(t_data *data)
{
	if (data->proc[data->j].redir && data->proc[data->j].redir[data->i])
	{
		while (data->proc[data->j].redir[data->l])
		{
			if (here_redirect(data))
				return (1);
			data->l++;
		}
	}
	return (0);
}

/*Handles redirect operants <, > and >>.*/
int	redir_exec(t_data *data)
{
	if (data->proc[data->j].redir && data->proc[data->j].redir[data->i])
	{
		while (data->proc[data->j].redir[data->i])
		{
			if (redout_loop(data) || redin_loop(data)
				|| appendout_loop(data))
				return (1);
			data->i++;
		}
	}
	return (0);
}
