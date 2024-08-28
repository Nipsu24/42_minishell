/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:11:07 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/28 10:45:59 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints the current working directory */
int	pwd(t_data *data)
{
	char	cwd[BUFF_SIZE];
	const char	*pwd;

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		pwd = get_env_var(data, "HOME");
		perror("pwd");
		chdir(pwd);
		return (1);
	}
	return (0);
}
