/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:33:42 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/15 15:26:56 by cesasanc         ###   ########.fr       */
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
	
}
