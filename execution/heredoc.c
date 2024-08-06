/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <mariusmeier@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:11:03 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/06 15:45:13 by mariusmeier      ###   ########.fr       */
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
static int	count_heres(t_data *data)
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
			 i++;
			 data->temp_here[j] = ft_ms_strjoin(data->temp_here[j], suffix);
			 if (!data->temp_env[j])
			 {
				free_arr_rev(data->temp_here, j);
				return (1);
			 }
			j++;
		}
		data->temp_here[j] = 0;
	}
	// j = -1;
	// printf("TEMP_FILES\n");
	// while (j++, data->temp_here[j])
	// 	printf("%s\n", data->temp_here[j]);
	return (0);
}

int	ft_heredoc(t_data *data)
{
	int		i;
	char	*tmp;
	char 	*trim_tmp;
	char	*nl;

	i = 0;
	tmp = NULL;
	nl = "\n";
	trim_tmp = NULL;
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
				data->proc[data->j].here_tmp = ft_ms_strjoin(data->proc[data->j].here_tmp, tmp);
				if (!data->proc[data->j].here_tmp)
					return (1);
			}
			if (ft_strnstr(data->proc[data->j].here_tmp,
					data->proc[data->j].redir[data->l + 1],
					ft_strlen(data->proc[data->j].here_tmp)))
			{
				printf("HERE TMP:\n%s", data->proc[data->j].here_tmp);
				trim_tmp = ft_strtrim(data->proc[data->j].here_tmp, tmp);
				free(data->proc[data->j].here_tmp);
				data->proc[data->j].here_tmp = NULL;
				data->proc[data->j].here_tmp = trim_tmp;
				free(tmp);
				tmp = NULL;
				printf("HERE TMP after trim:\n%s", data->proc[data->j].here_tmp);
				break ;
			}
			free(tmp);
			tmp = NULL;
		}
		if (no_other_heredoc(data))
		{
			printf("TEMP_FILES: %s\n", data->temp_here[i]);
			data->proc[data->j].fd[data->k] = open(data->temp_here[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			write(data->proc[data->j].fd[data->k], data->proc[data->j].here_tmp, ft_strlen(data->proc[data->j].here_tmp));
			close (data->proc[data->j].fd[data->k]);
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
