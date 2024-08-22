/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:33:42 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/20 14:47:05 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(t_data *data)
{
	const char	*home;

	home = get_env_var(data, "HOME");
	if (!home)
	{
		perror("Error: HOME environment variable not set\n");
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("Error changing directory to HOME");
		return (1);
	}
	update_var(data, (ft_strjoin("PWD=", home)));
//	free(home);
	return (0);
}

static int	do_cd(char **array, t_data *data)
{
	char	*newpwd;

	newpwd = NULL;
	ft_strlcpy(data->newpwd, array[1], sizeof(data->newpwd));
	if (chdir(data->newpwd) == -1)
	{
		perror("Error changing directory");
		return (1);
	}
	newpwd = ft_strjoin("PWD=", data->newpwd);
	if (!newpwd)
	{
		perror("Error memory allocation");
		free(newpwd);
		return (1);
	}
	update_var(data, newpwd);
	update_var(data, (ft_strjoin("OLDPWD=", data->oldpwd)));
	free(newpwd);
	return (0);
}

int	cd(char **array, t_data *data)
{
	int	i;

	i = len_array(array);
	if (!getcwd(data->oldpwd, sizeof(data->oldpwd)))
	{
		perror("Error getting cwd");
		return (1);
	}
	if (i == 1)
		return (cd_home(data));
	else if (i == 2)
		return (do_cd(array, data));
	else
	{
		perror("cd: too many arguments");
		return (1);
	}
}
