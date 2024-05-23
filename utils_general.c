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
		free(av[i]);
		av[i] = NULL;
		i--;
	}
	free(av);
	av = NULL;
	return (NULL);
}
