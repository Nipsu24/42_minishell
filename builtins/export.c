/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:04:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/11 12:51:23 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
	{
		printf("Error: No environment variables found\n");
		return ;
	}
	while (env[i])
	{
		printf("declare -x ");
		printf("%s\n", env[i]);
		i++;
	}
}

int	export(t_data *data, char *array)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (array[i])
	{
		if (add_var(data, array[i]))
			ret = 1;
		i++;
	}
	if (i == 1)
		print_export_env(data->temp_env);
	return (ret);
}
