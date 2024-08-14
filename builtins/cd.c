/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:33:42 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/13 14:06:25 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **array, t_data *data)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	if (!getcwd(data->oldpwd, sizeof(data->oldpwd)))
	{
		perror("Error getting cwd");
		return (1);
	}
	if (i == 1)
	{
		if (chdir(array[1]))
		{
			perror("Error changing directory");
			return (1);
		}
	}
	else if (i == 2 && !ft_strncmp(array[1], "-", 1))
	{
		if (chdir(data->oldpwd))
		{
			perror("Error changing directory");
			return (1);
		}
	}
	else
	{
		if (chdir(array[1]))
		{
			perror("Error changing directory");
			return (1);
		}
	}
}
