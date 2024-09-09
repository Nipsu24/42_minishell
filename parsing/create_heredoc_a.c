/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:11:03 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/09 14:06:22 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*In the first iteration of the ft_heredoc while loop,
  content of tmp (from readline function) gets duplicated
  instead of string joined into empty here_tmp string,
  in order to not cause any issues with the strjoin function
  when passing a NULL String to it. 2nd if statement for check
  if already first line constists of delimiter.*/
int	dup_for_empty_here_tmp(t_data *data)
{
	data->proc[data->j].here_tmp = ft_strdup(data->tmp);
	if (!data->proc[data->j].here_tmp)
	{
		free_str(&data->tmp);
		return (1);
	}
	if (ft_strncmp(data->tmp, data->proc[data->j].redir[data->l + 1],
			ft_strlen(data->tmp)) == 0)
	{
		free_str(&data->tmp);
		data->delim_fst_line = 1;
		return (-1);
	}
	return (0);
}

/*Helper function of ft_heredoc, joins new line character
  at end of here_tmp string and checks if the tmp string which
  contains the read line matches with the heredoc delimiter.
  If this is the case, returns -1 which is indicator in
  ft_heredoc function to break out of while loop. If not
  the case, the read line (tmp) is joind at the end of
  here_tmp file*/
int	eof_detected(t_data *data)
{
	data->proc[data->j].here_tmp
		= ft_ms_strjoin(data->proc[data->j].here_tmp, data->nl);
	if (!data->proc[data->j].here_tmp)
		return (1);
	if (!ft_strncmp(data->tmp, data->proc[data->j].redir[data->l + 1],
			ft_strlen(data->tmp)))
	{
		free_str(&data->tmp);
		return (-1);
	}
	else
	{
		data->proc[data->j].here_tmp
			= ft_ms_strjoin(data->proc[data->j].here_tmp, data->tmp);
		if (!data->proc[data->j].here_tmp)
		{
			free_str(&data->tmp);
			return (1);
		}
	}
	return (0);
}

/*Handles heredoc creation within a process.*/
static int	ft_heredoc(t_data *data)
{
	if (ft_strncmp(data->proc[data->j].redir[data->l], "<<", 2) == 0)
	{
		if (here_while_loop(data))
			return (1);
		if (file_create_n_write(data))
			return (1);
	}
	return (0);
}

/*Main function for creating heredocs.*/
int	create_heredocs(t_data *data)
{
	if (data->proc[data->j].redir && data->proc[data->j].redir[data->l])
	{
		while (data->proc[data->j].redir[data->l])
		{
			if (ft_heredoc(data))
				return (1);
			data->l++;
		}
	}
	return (0);
}
