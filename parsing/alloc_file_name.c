/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <mariusmeier@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:19:07 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/08 10:23:00 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks occurence of heredocs in each process for determining how
  many temporary files are need to be created. Breaks out of loop 
  of each process count as soon as one heredoc is encountered
  as for each process only maximum one heredoc file needs to be
  set up*/
static int	count_heres(t_data *data)
{
	int	j;
	int	l;
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

/*Helper function of alloc_here_filename, joins prefix, file number
  and suffix for filename creation into 2d array.*/
static int	join_file_name(t_data *data, char *prefix,
									char *suffix, int amount_files)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (j < amount_files)
	{
		data->temp_here[j] = ft_ms_strjoin_rev_free(prefix, ft_itoa(i));
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
	return (0);
}

/*Checks amount of needed temporary files for the heredocs and
  allocates memory for the respective filenames in a 2d array.
  Structure of filenames is always 
  prefix -> file_nbr(created with itoa) -> suffix.*/
int	alloc_here_filename(t_data *data)
{
	int		amount_files;
	char	*prefix;
	char	*suffix;
	// int		j;

	prefix = "file_";
	suffix = ".txt";
	// j = 0;
	amount_files = count_heres(data);
	if (amount_files > 0)
	{
		data->temp_here = malloc (sizeof(char *) * amount_files + 1);
		if (!data->temp_here)
			return (1);
		if (join_file_name(data, prefix, suffix, amount_files))
			return (1);
	}
	// j = -1;
	// printf("TEMP_FILES\n");
	// while (j++, data->temp_here[j])
	// 	printf("%s\n", data->temp_here[j]);
	return (0);
}
