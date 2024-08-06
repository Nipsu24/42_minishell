/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:11:03 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/06 12:12:42 by mmeier           ###   ########.fr       */
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

/*Checks occurence of heres in each process for determining how
  many temp. files need to be created. Breaks out of loop of
  each process count as soon as one heredoc is encountered
  as for each process only maximum one heredoc file needs to be
  set up*/
int	count_heres(t_data *data)
{
	int	j;
	int l;
	int	count;
	int	start_count;

	j = 0;
	l = 0;
	count = 0;
	start_count = 0;
	while (j < data->proc_nbr)
	{
		l = 0;
		start_count = count;
		while (data->proc[j].redir[l])
		{
			if (ft_strncmp(data->proc[j].redir[l], "<<", 2) == 0)
				count++;
			if (start_count < count)
				break ;
			l++;
		}
		j++;
	}
	return (count);
}

int	alloc_here_tmp(t_data *data)
{
	int		amount_files;
	char	*prefix;
	char 	*suffix;
	int		j;
	int		i;

	prefix = "file_";
	suffix = ".txt";
	j = 0;
	i = 0;
	amount_files = count_heres(data);
	if (amount_files > 0)
	{
		data->temp_here = malloc (sizeof(char *) * amount_files + 1);
		if (!data->temp_here)
			return (1);
		while (j < amount_files)
		{
			 data->temp_here[j] = ft_strjoin(prefix, ft_itoa(i));
			 if (!data->temp_here[j])
			 {
				free_arr_rev(data->temp_here, j);
				return (1);
			 }
			 data->temp_here[j] = ft_strjoin()
			 	
			 
			
			j++;
		}
		
	}
	return (0);
}


int	ft_heredoc(t_data *data)
{
	if (ft_strncmp(data->proc[data->j].redir[data->l], "<<", 2) == 0)
	{
		while (1)
		{
			data->proc[data->j].here_tmp = readline("> ");
			if (!data->proc[data->j].here_tmp)
				return (1);
			if (ft_strnstr(data->proc[data->j].here_tmp,
					data->proc[data->j].redir[data->l + 1],
					ft_strlen(data->proc[data->j].redir[data->l + 1])))
				break ;
			if (no_other_heredoc(data))
			{
				
			}
		}
	}
	return (0);
}	
		
		
// 		data->proc[data->j].fd[data->k]
// 			= open(data->proc[data->j].redir[data->i + 1], O_RDONLY);
// 		if (data->proc[data->j].fd[data->k] < 0)
// 		{
// 			printf("%s: No such file or directory\n",
// 				data->proc[data->j].redir[data->i + 1]);
// 			return (1);
// 		}
// 		if (no_other_redin(data))
// 		{
// 			dup2(data->proc[data->j].fd[data->k], STDIN_FILENO);
// 			close(data->proc[data->j].fd[data->k]);
// 			if (data->proc[data->j].redir[data->i + 2] != NULL)
// 				data->proc[data->j].fd[data->k]++;
// 			return (0);
// 		}
// 		else
// 		{
// 			close (data->proc[data->j].fd[data->k]);
// 			data->proc[data->j].fd[data->k]++;
// 		}
// 	}
// 	return (0);
// }
