/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <mariusmeier@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:29:54 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/08/08 14:24:58 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*Redirects heredocfile's content into std input*/
static int	here_redirect(t_data *data)
{
	data->proc[data->j].fd[data->k]
			= open(data->temp_here[data->m], O_RDONLY);
	if (data->proc[data->j].fd[data->k] < 0)
	{
		printf("%s: No such file or directory\n",
			data->temp_here[data->m]);
		return (1);
	}
	dup2(data->proc[data->j].fd[data->k], STDIN_FILENO);
	close(data->proc[data->j].fd[data->k]);
	return (0);
}

/*Checks first, if no further heredoc is detected in the process.
  If no further detected, creates temporary heredoc file by giving
  the previously created filename to the open function as argument.
  Then writes content of here_tmp string into file and closes fd.
  Indices k and m are incremented for potential next loop (if
  heredocs exist in other processes).*/
int	file_create_n_write(t_data *data)
{
	if (no_other_heredoc(data))
	{
		data->proc[data->j].fd[data->k]
			= open(data->temp_here[data->m],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(data->proc[data->j].fd[data->k],
			data->proc[data->j].here_tmp,
			ft_strlen(data->proc[data->j].here_tmp));
		close (data->proc[data->j].fd[data->k]);
		free_str(&data->tmp);
		if (here_redirect(data))
			return (1);
		data->k++;
		data->m++;
	}
	else
	{
		free_str(&data->tmp);
		free_str(&data->proc[data->j].here_tmp);
	}
	return (0);
}
