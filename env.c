/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:26:55 by mmeier            #+#    #+#             */
/*   Updated: 2024/07/31 11:28:25 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Creates copy of env var in order to being able of modifying this copy
  later on in the course of the shell execution*/
char	**ft_copy_env(char **env, char **cpy_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[j])
		j++;
	cpy_env = (char **) malloc (sizeof(char *) * (j + 1));
	if (!cpy_env)
		return (NULL);
	while (env[i])
	{
		cpy_env[i] = ft_substr(env[i], 0, ft_strlen(env[i]));
		if (!cpy_env[i])
			return (free_arr_rev(cpy_env, i));
		i++;
	}
	return (cpy_env);
}

/*Prints the envrironmental variable*/
void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
