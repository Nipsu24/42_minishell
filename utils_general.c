/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:10:48 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/23 16:33:10 by mmeier           ###   ########.fr       */
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
