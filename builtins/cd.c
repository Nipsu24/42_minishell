/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:33:42 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/23 22:00:53 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to change directory to HOME, if HOME is not set, return error. Then
   update PWD variable with the new path */
static int	cd_home(t_data *data)
{
	const char	*home;
	char		*pwd;

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
