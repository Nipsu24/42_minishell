/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:19:07 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/14 11:56:12 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks occurence of heredoc in avprocess for determining if
  a temporary files needs to be created. Breaks out of loop 
  as soon as one heredoc is encountered in the process
  as for each process only maximum one heredoc file needs to be
  set up.*/

static int	here_in_prc(t_data *data)
{
	int	l;
	int	count;

	l = 0;
	count = 0;
	if (data->proc[data->j].redir != NULL)
	{
		while (data->proc[data->j].redir[l])
		{
			if (ft_strncmp(data->proc[data->j].redir[l], "<<", 2) == 0)
			{
				count++;
				break ;
			}
			l++;
		}
	}
	return (count);
}

/*Helper function of alloc_here_filename, joins prefix, file number
  and suffix into one string for filename creation.*/
static int	join_file_name(t_data *data, char *prefix, char *suffix)
{
	data->proc[data->j].here_name = ft_ms_strjoin_rev_free(prefix, ft_itoa(data->i));
	if (!data->proc[data->j].here_name)
		return (1);
	data->i++;
	data->proc[data->j].here_name = ft_ms_strjoin(data->proc[data->j].here_name, suffix);
	if (!data->proc[data->j].here_name)
		return (1);
	return (0);
}

/*Checks if a temporary hidden file (heredoc) is needed within
  a process, allocates memory for the respective filename string
  and populates string. Structure of filenames is always 
  prefix -> file_nbr(created with itoa) -> suffix.*/
int	alloc_here_filename(t_data *data)
{
	char	*prefix;
	char	*suffix;

	data->j = 0;
	data->i = 0;
	prefix = ".file_";
	suffix = ".txt";
	while (data->j < data->proc_nbr)
	{
		if (here_in_prc(data))
		{
			if (join_file_name(data, prefix, suffix))
				return (1);
		}
		data->j++;
	}
	return (0);
}
