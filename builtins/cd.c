/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:33:42 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/04 12:55:55 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to change directory to HOME, if HOME is not set, return error. Then
   update PWD variable with the new path */
int	cd_home(t_data *data)
{
	const char	*home;
	char		*pwd;

	home = get_env_var(data, "HOME");
	if (!home || !*home)
	{
		write(STDERR_FILENO, "Error: HOME environment variable not set\n", 41);
		return (1);
	}
	if (chdir(home) == -1)
	{
		write(STDERR_FILENO, "Error changing directory to HOME", 32);
		return (1);
	}
	pwd = ft_strjoin("PWD=", home);
	update_var(data, pwd);
	free_str(&pwd);
	return (0);
}

/* Function to change directory to the path given in the argument. If the path
   is not valid, return error. Then update PWD and OLDPWD variables with the new
   path */
static int	do_cd(char **array, t_data *data)
{
	char	*newpwd;
	char	*oldpwd;

	newpwd = NULL;
	oldpwd = NULL;
	ft_strlcpy(data->newpwd, array[1], sizeof(data->newpwd));
	if (chdir(data->newpwd) == -1)
	{
		write(STDERR_FILENO, "Error changing directory", 25);
		return (1);
	}
	newpwd = ft_strjoin("PWD=", data->newpwd);
	if (!newpwd)
	{
		write(STDERR_FILENO, "Error memory allocation", 24);
		free(newpwd);
		return (1);
	}
	update_var(data, newpwd);
	oldpwd = ft_strjoin("OLDPWD=", data->oldpwd);
	update_var(data, oldpwd);
	free_str(&newpwd);
	free_str(&oldpwd);
	return (0);
}

/* Function to change directory. If no arguments are given, change to HOME. If
   more than one argument is given, return error. If one argument is given,
   change to the path given in the argument */
int	cd(char **array, t_data *data)
{
	int	i;

	i = len_array(array);
	if (!getcwd(data->oldpwd, sizeof(data->oldpwd)))
	{
		write(STDERR_FILENO, "Error getting cwd", 17);
		return (1);
	}
	if (i == 1)
		return (cd_home(data));
	else if (i == 2)
		return (do_cd(array, data));
	else
	{
		write(STDERR_FILENO, "cd: too many arguments", 22);
		return (1);
	}
}
