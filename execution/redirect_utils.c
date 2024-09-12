/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:39:05 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/09/12 15:29:28 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns 0 in case another redirect out '>' or '>>' operator has been found in
  redir array, otherwise returns 1.*/
int	no_other_redout(t_data *data)
{
	int	i;
	int	j;

	i = data->i;
	j = data->j;
	i++;
	while (data->proc[j].redir[i])
	{
		if (ft_strncmp(data->proc[j].redir[i], ">", 1) == 0)
			return (0);
		i++;
	}
	return (1);
}

/*Returns 0 in case another redirect in '<' operator has been found in
  redir array, otherwise returns 1.*/
int	no_other_redin(t_data *data)
{
	int	i;
	int	j;

	i = data->i;
	j = data->j;
	i++;
	while (data->proc[j].redir[i])
	{
		if (ft_strncmp(data->proc[j].redir[i], "<", 1) == 0
			&& !data->proc[j].redir[i][1])
			return (0);
		i++;
	}
	return (1);
}

/*Checks if there is any other heredoc in a process. If yes,
  returns 0.*/
int	no_other_heredoc(t_data *data)
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

/*Is checking specific errno code and prints respective error message
  in course of redirection handling.*/
int	check_value_of_errno(t_data *data, char *file_name)
{
	if (errno == EACCES)
		update_exit_status(data, 1, "Error", "Permission denied");
	if (errno == EISDIR)
		update_exit_status(data, 1, "Error", "Is a directory");
	if (errno == ENOENT)
		update_exit_status(data, 1, file_name, "No such file or directory");
	return (1);
}
