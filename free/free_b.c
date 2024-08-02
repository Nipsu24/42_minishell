/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <mariusmeier@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:03:23 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/02 16:26:10 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*Frees 2d array - char version*/
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

/*Void version of free_arr*/
void	free_arr_void(char **arr)
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