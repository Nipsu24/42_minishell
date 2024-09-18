/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:58 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/18 12:00:34 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees int array and sets freed pointer to NULL.*/
void	free_int_arr(int **arr)
{
	if (*arr == NULL)
		return ;
	free(*arr);
	*arr = NULL;
}

/*Frees 2d int array from the start.*/
void	free_2d_int_arr(t_data *data, int ***arr)
{
	int	n;
	int	j;

	j = 0;
	n = data->proc_nbr;
	if (*arr == NULL)
		return ;
	while (j < n)
	{
		if ((*arr)[j] != NULL)
		{
			free((*arr)[j]);
			(*arr)[j] = NULL;
		}
		j++;
	}
	free(*arr);
	*arr = NULL;
}

/*Frees 2d int array in reversed order in case of malloc failure.*/
void	free_2d_int_arr_rev(int ***arr, int j)
{
	if (*arr == NULL)
		return ;
	while (j > 0)
	{
		{
			free((*arr)[j - 1]);
			(*arr)[j -1] = NULL;
		}
		j--;
	}
	free(*arr);
	*arr = NULL;
}

/*Used if amount of pipes exceeded*/
void	free_parser(t_data *data, int exit_flag)
{
	if (data->tokens && data->tokens[0])
		free_arr_void(&data->tokens);
	if (data->token_list)
	{
		free(data->token_list);
		data->token_list = NULL;
	}
	if (exit_flag)
		exit(data->exit_status);
}

/*Frees all proc_structs in order.*/
void	free_proc_structs(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->proc_nbr)
	{
		if (data->proc[j].cmd != NULL)
			free_arr_void(&data->proc[j].cmd);
		if (data->proc[j].redir != NULL)
			free_arr_void(&data->proc[j].redir);
		if (data->proc[j].path != NULL)
			free_str(&data->proc[j].path);
		if (data->proc[j].fd != NULL)
			free_int_arr(&data->proc[j].fd);
		if (data->proc[j].here_tmp != NULL)
			free_str(&data->proc[j].here_tmp);
		if (data->proc[j].here_name != NULL)
			free_str(&data->proc[j].here_name);
		j++;
	}
	free(data->proc);
	data->proc = NULL;
}
