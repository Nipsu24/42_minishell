/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:11:03 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/07 11:19:55 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_heredoc(t_data *data)
{
	char	*tmp;
	char	*nl;

	tmp = NULL;
	nl = "\n";
	if (ft_strncmp(data->proc[data->j].redir[data->l], "<<", 2) == 0)
	{
		while (1)
		{
			tmp = readline("> ");
			if (!tmp)
				return (1);
			if (!data->proc[data->j].here_tmp)
			{
				data->proc[data->j].here_tmp = ft_strdup(tmp);
				if (!data->proc[data->j].here_tmp)
					return (1);
			}
			else
			{
				data->proc[data->j].here_tmp = ft_ms_strjoin(data->proc[data->j].here_tmp, nl);
				if (!data->proc[data->j].here_tmp)
					return (1);
				if (ft_strncmp(tmp, data->proc[data->j].redir[data->l + 1], ft_strlen(tmp)) == 0)
				{
					printf("HERE TMP:\n%s", data->proc[data->j].here_tmp);
					free_str(&tmp);
					break ;
				}
				else
				{
					data->proc[data->j].here_tmp = ft_ms_strjoin(data->proc[data->j].here_tmp, tmp);
					if (!data->proc[data->j].here_tmp)
					{
						free_str(&tmp);
						return (1);
					}
				}
			}
			free(tmp);
			tmp = NULL;
		}
		if (no_other_heredoc(data))
		{
			printf("TEMP_FILES: %s\n", data->temp_here[data->m]);
			data->proc[data->j].fd[data->k] = open(data->temp_here[data->m], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			write(data->proc[data->j].fd[data->k], data->proc[data->j].here_tmp, ft_strlen(data->proc[data->j].here_tmp));
			close (data->proc[data->j].fd[data->k]);
			free_str(&tmp);
			free_str(&data->temp_here[data->m]);
			data->k++;
			data->m++;
		}
		else
		{
			free_str(&tmp);
			free_str(&data->proc[data->j].here_tmp);
		}
	}
	return (0);
}	
