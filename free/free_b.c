/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:03:23 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/13 14:39:34 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees 2d array in reversed order e.g. for failed copy
  of env variable in ft_copy_env function*/
char	**free_arr_rev(char ***av, int i)
{
	if (*av == NULL)
		return (NULL);
	while (i > 0)
	{
		free((*av)[i - 1]);
		(*av)[i - 1] = NULL;
		i--;
	}
	free(*av);
	*av = NULL;
	return (NULL);
}

/*Frees 2d array - char version*/
char	**free_arr(char ***arr)
{
	int	j;

	j = 0;
	if (*arr == NULL)
		return (NULL);
	while ((*arr)[j])
	{
		free((*arr)[j]);
		(*arr)[j] = NULL;
		j++;
	}
	free(*arr);
	*arr = NULL;
	return (NULL);
}

/*Void version of free_arr*/
void	free_arr_void(char ***arr)
{
	int	j;

	j = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[j])
	{
		free((*arr)[j]);
		(*arr)[j] = NULL;
		j++;
	}
	free(*arr);
	*arr = NULL;
}

/*Frees string and sets pointer to NULL. Caller function
  should pass address of str to this function.*/
void	free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

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
	while (j < n)
	{
		if ((*arr)[j] != NULL)
		{
			free((*arr)[j]);
			*arr[j] = NULL;
		}
		j++;
	}
	free(*arr);
	arr = NULL;
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
