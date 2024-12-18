/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:03:59 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/18 11:56:43 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks first, if no further heredoc is detected in the process.
  If no further detected, creates temporary heredoc file by giving
  the previously created filename (from alloc_here_filename function)
  or NULL in case delimiter is encountered directly on first line
  (delim_fst_line == 1 from dup_for_empty_here function) to the 'open'
  function as argument. Then writes content of here_tmp string into 
  file and closes fd.*/
int	file_create_n_write(t_data *data)
{
	if (no_other_heredoc(data))
	{
		data->proc[data->j].fd[0]
			= open(data->proc[data->j].here_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->delim_fst_line == 1 || data->flag_cntlr_d)
			write(data->proc[data->j].fd[0],
				NULL, 0);
		else
			write(data->proc[data->j].fd[0],
				data->proc[data->j].here_tmp,
				ft_strlen(data->proc[data->j].here_tmp));
		close (data->proc[data->j].fd[0]);
		free_str(&data->tmp);
	}
	else
	{
		free_str(&data->tmp);
		free_str(&data->proc[data->j].here_tmp);
	}
	return (0);
}

/* Cleanup and exit */
static int	cleanup_and_exit(int stdin_fd)
{
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	return (0);
}

/* Handle SIGINT or empty tmp */
static int	handle_sigint_or_tmp(t_data *data, int stdin_fd)
{
	if (g_sigint)
		return (update_exit_status(data, 130, NULL, NULL), 1);
	if (!data->tmp)
	{
		cleanup_and_exit(stdin_fd);
		data->flag_cntlr_d = 1;
		return (1);
	}
	if (!data->proc[data->j].here_tmp)
	{
		if (dup_for_empty_here_tmp(data) == -1)
			return (1);
	}
	else
	{
		data->return_val = eof_detected(data);
		if (data->return_val == -1)
			return (1);
		if (data->return_val == 1)
		{
			cleanup_and_exit(stdin_fd);
			return (1);
		}
	}
	return (0);
}

/* Main while loop for writing into here doc */
int	here_while_loop(t_data *data)
{
	int	stdin_fd;

	signal(SIGINT, here_sig_int);
	stdin_fd = dup(STDIN_FILENO);
	if (stdin_fd == -1)
		return (1);
	while (1)
	{
		g_sigint = false;
		data->flag_cntlr_d = 0;
		data->delim_fst_line = 0;
		data->tmp = readline("> ");
		if (handle_sigint_or_tmp(data, stdin_fd))
			break ;
		free_str(&data->tmp);
	}
	return (cleanup_and_exit(stdin_fd));
}
