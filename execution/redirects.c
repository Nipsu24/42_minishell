/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:42:18 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/28 12:51:36 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks for '<' and redirects respective file's input to command in case 
  there is no further redin file in redir array. If further redin file in
  array, current file only gets read and fd index is moved further. 
  FD index is also moved further in case there are further redirect operants
  in array*/
int	redin_loop(t_data *data)
{
	if (ft_strncmp(data->proc[data->j].redir[data->i], "<", 1) == 0
		&& !data->proc[data->j].redir[data->i][1])
	{
		data->proc[data->j].fd[data->k]
			= open(data->proc[data->j].redir[data->i + 1], O_RDONLY);
		if (data->proc[data->j].fd[data->k] < 0)
		{
			printf("%s: No such file or directory\n",
				data->proc[data->j].redir[data->i + 1]);
			return (1);
		}
		if (no_other_redin(data))
		{
			if (dup2(data->proc[data->j].fd[data->k], STDIN_FILENO) < 0)
				return (1);
			close(data->proc[data->j].fd[data->k]);
			if (data->proc[data->j].redir[data->i + 2] != NULL)
				data->proc[data->j].fd[data->k]++;
			return (0);
		}
		else
		{
			close (data->proc[data->j].fd[data->k]);
			data->proc[data->j].fd[data->k]++;
		}
	}
	return (0);
}

/*Checks for '>>' and redirects output of command to respective file and 
  appends it there in case there is no further redir out file or file in
  redir array. If further redout file or >> in array, current file only 
  gets opened and fd index is moved further. FD index is also moved further
  in case there are any other further redirect operants in array*/
int	appendout_loop(t_data *data)
{
	if (ft_strncmp(data->proc[data->j].redir[data->i], ">>", 2) == 0)
	{
		data->proc[data->j].fd[data->k]
			= open(data->proc[data->j].redir[data->i + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->proc[data->j].fd[data->k] < 0)
		{
			perror("open failed\n");
			return (1);
		}
		if (no_other_redout(data))
		{
			if (dup2(data->proc[data->j].fd[data->k], STDOUT_FILENO) < 0)
				return (1);
			close(data->proc[data->j].fd[data->k]);
			if (data->proc[data->j].redir[data->i + 2] != NULL)
				data->proc[data->j].fd[data->k]++;
			return (0);
		}
		else
		{
			close (data->proc[data->j].fd[data->k]);
			data->proc[data->j].fd[data->k]++;
		}
	}
	return (0);
}

/*Checks for '>' and redirects output of command to respective file in case 
  there is no further redir out file in redir array. If further redout file
  in array, current file only gets opened and fd index is moved further.
  FD index is also moved further in case there are any other further
  redirect operants in array*/
int	redout_loop(t_data *data)
{
	if (ft_strncmp(data->proc[data->j].redir[data->i], ">", 1)
		== 0 && !data->proc[data->j].redir[data->i][1])
	{
		data->proc[data->j].fd[data->k]
			= open(data->proc[data->j].redir[data->i + 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->proc[data->j].fd[data->k] < 0)
			return (1);
		if (no_other_redout(data))
		{
			if (dup2(data->proc[data->j].fd[data->k], STDOUT_FILENO) < 0)
				return (1);
			close(data->proc[data->j].fd[data->k]);
			if (data->proc[data->j].redir[data->i + 2] != NULL)
				data->proc[data->j].fd[data->k]++;
			return (0);
		}
		else
		{
			close (data->proc[data->j].fd[data->k]);
			data->proc[data->j].fd[data->k]++;
		}
	}
	return (0);
}

/*Redirects heredocfile's content into std input*/
int	here_redirect(t_data *data)
{
	if (ft_strncmp(data->proc[data->j].redir[data->l], "<<", 2) == 0)
	{
		if (no_other_heredoc(data))
		{
			data->proc[data->j].fd[data->k]
				= open(data->proc[data->j].here_name, O_RDONLY);
			if (data->proc[data->j].fd[data->k] < 0)
			{
				printf("%s: No such file or directory\n",
					data->proc[data->j].here_name);
				return (1);
			}
			if (dup2(data->proc[data->j].fd[data->k], STDIN_FILENO) < 0)
				return (1);
			close(data->proc[data->j].fd[data->k]);
			if (data->proc[data->j].redir[data->l + 2] != NULL)
				data->proc[data->j].fd[data->k]++;
		}
	}
	return (0);
}
