/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:03:23 by mmeier            #+#    #+#             */
/*   Updated: 2024/07/25 13:05:12 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees relevant parts of the main struct. Last if-statement still
  to be investigated if sufficient.*/
void	free_all(t_data *data)
{
	int	j;
	//int	i;

	j = 0;
	//i = 0;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens && data->tokens[j])
	{
		while (data->tokens[j])
		{
			free(data->tokens[j]);
			data->tokens[j] = NULL;
			j++;
		}
		free(data->tokens);
		data->tokens = NULL;
	}
	// if (data->prcs && data->prcs[i])
	// {
	// 	while (data->prcs[i])
	// 	{
	// 		free(data->prcs[i]);
	// 		data->prcs[i] = NULL;
	// 		i++;
	// 	}
	// 	free(data->prcs);
	// 	data->prcs = NULL;
	// }
	if (data->token_list)
	{
		free(data->token_list);
		data->token_list = NULL;
	}
}
/*Frees 2d array in reversed order e.g. for failed copy
  of env variable in ft_copy_env function*/
char	**free_arr_rev(char **av, int i)
{
	if (av[i] == NULL || av == NULL)
		return (NULL);
	while (i > 0)
	{
		free(av[i - 1]);
		av[i - 1] = NULL;
		i--;
	}
	free(av);
	av = NULL;
	return (NULL);
}

/*dublicate with above function!! to be cleand up!n*/
char	**ft_free(char **result, size_t j)
{
	while (j > 0)
	{
		free(result[j - 1]);
		j--;
	}
	free(result);
	result = NULL;
	return (NULL);
}

char	**free_arr(char **arr)
{
	int	j;

	j = 0;
	if (arr && arr[j])
	{
		while (arr[j])
		{
			free(arr[j]);
			arr[j] = NULL;
			j++;
		}
		free(arr);
		arr = NULL;
	}
	return (NULL);
}

/*Helper function of free_proc_arrays_rev, loops through redir array.*/
static void	free_redir(t_data *data)
{
	while (data->proc[data->j].redir[data->l] > 0)
	{
		free(data->proc[data->j].redir[data->l - 1]);
		data->l--;
	}
}

/*Frees proc arrays in case of failed memory allocation for either cmd or
  redir arrays*/
int	free_proc_arr_rev(t_data *data)
{
	while (data->j >= 0)
	{
		if (data->proc[data->j].cmd[data->k] != NULL
			|| data->proc[data->j].cmd != NULL)
		{
			while (data->proc[data->j].cmd[data->k] > 0)
			{
				free(data->proc[data->j].cmd[data->k - 1]);
				data->k--;
			}
			free(data->proc[data->j].cmd);
			data->proc[data->j].cmd = NULL;
		}
		if (data->proc[data->j].redir[data->l] != NULL
			|| data->proc[data->j].redir != NULL)
		{
			free_redir(data);
			free(data->proc[data->j].redir);
			data->proc[data->j].redir = NULL;
		}
		data->j--;
	}
	return (1);
}