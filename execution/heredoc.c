/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:11:03 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/07 15:52:51 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*In the first iteration of the ft_heredoc while loop,
  content of tmp (from readline function) gets duplicated
  instead of string joined into empty here_tmp string,
  in order to not cause any issues with the strjoin function
  when passing a NULL String to it.*/
static int	dup_for_empty_here_tmp(t_data *data)
{
	data->proc[data->j].here_tmp = ft_strdup(data->tmp);
	if (!data->proc[data->j].here_tmp)
		return (1);
	return (0);
}

/*Helper function of ft_heredoc, joins new line character
  at end of here_tmp string and checks if the tmp string which
  contains the read line matches with the heredoc delimiter.
  If this is the case, returns -1 which is indicator in
  ft_heredoc function to break out of while loop. If not
  the case, the read line (tmp) is joind at the end of
  here_tmp file*/
static int	eof_detected(t_data *data)
{
	data->proc[data->j].here_tmp
		= ft_ms_strjoin(data->proc[data->j].here_tmp, data->nl);
	if (!data->proc[data->j].here_tmp)
		return (1);
	if (ft_strncmp(data->tmp, data->proc[data->j].redir[data->l + 1],
			ft_strlen(data->tmp)) == 0)
	{
		//printf("HERE TMP:\n%s", data->proc[data->j].here_tmp);
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

/*Checks if there is any other heredoc in a process. If yes,
  returns 0.*/
static int	no_other_heredoc(t_data *data)
{
	int	l;
	int	j;

	l = data->l;
	j = data->j;
	l++;
	while (data->proc[j].redir[l])
	{
		if (ft_strncmp(data->proc[j].redir[l], "<<", 2) == 0)
			return (0);
		l++;
	}
	return (1);
}

/*Checks first, if no further heredoc is detected in the process.
  If no further detected, creates temporary heredoc file by giving
  the previously created filename to the open function as argument.
  Then writes content of here_tmp string into file and closes fd.
  Indices k and m are incremented for potential next loop (if
  heredocs exist in other processes).*/
static void	file_create_n_write(t_data *data)
{
	if (no_other_heredoc(data))
	{
		//printf("TEMP_FILES: %s\n", data->temp_here[data->m]);
		data->proc[data->j].fd[data->k]
			= open(data->temp_here[data->m],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(data->proc[data->j].fd[data->k],
			data->proc[data->j].here_tmp,
			ft_strlen(data->proc[data->j].here_tmp));
		close (data->proc[data->j].fd[data->k]);
		//insert redirection handling here
		free_str(&data->tmp);
		data->k++;
		data->m++;
	}
	else
	{
		free_str(&data->tmp);
		free_str(&data->proc[data->j].here_tmp);
	}
}

/*Handles heredoc creation within a process.*/
int	ft_heredoc(t_data *data)
{
	if (ft_strncmp(data->proc[data->j].redir[data->l], "<<", 2) == 0)
	{
		while (1)
		{
			data->tmp = readline("> ");
			if (!data->tmp)
				return (1);
			if (!data->proc[data->j].here_tmp)
			{
				if (dup_for_empty_here_tmp(data))
					return (1);
			}
			else
			{	
				data->return_val = eof_detected(data);
				if (data->return_val == -1)
					break ;
				if (data->return_val == 1)
					return (1);
			}
			free_str(&data->tmp);
		}
		file_create_n_write(data);
	}
	return (0);
}
