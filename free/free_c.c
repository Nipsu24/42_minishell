/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:58 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/28 11:13:57 by mmeier           ###   ########.fr       */
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
	n = data->proc_nbr -1;
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
