/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:03:59 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/05 23:30:27 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks first, if no further heredoc is detected in the process.
  If no further detected, creates temporary heredoc file by giving
  the previously created filename (from alloc_here_filename function)
  or NULL in case delimiter is encountered directly on first line
  (delim_fst_line == 1 from dup_for_empty_here function) to the 'open'
  function as argument. Then writes content of here_tmp string into 
  file and closes fd. Index k is incremented for potential next loop 
  (if further files for other redirects need to be set up).*/
int	file_create_n_write(t_data *data)
{
	if (no_other_heredoc(data))
	{
		data->proc[data->j].fd[data->k]
			= open(data->proc[data->j].here_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->delim_fst_line == 1 || data->flag_cntlr_d)
			write(data->proc[data->j].fd[data->k],
				NULL, 0);
		else
			write(data->proc[data->j].fd[data->k],
				data->proc[data->j].here_tmp,
				ft_strlen(data->proc[data->j].here_tmp));
		close (data->proc[data->j].fd[data->k]);
		free_str(&data->tmp);
		data->k++;
	}
	else
	{
		free_str(&data->tmp);
		free_str(&data->proc[data->j].here_tmp);
	}
	return (0);
}
