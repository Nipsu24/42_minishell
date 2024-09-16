/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:11:07 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/16 22:27:12 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints the current working directory */
int	pwd(t_data *data)
{
	char	cwd[BUFF_SIZE];
	char	*home;

	home = get_env_var(data, "HOME");
	if (!home || !*home)
		return (1);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		update_exit_status(data, 1, "pwd", "Error getting cwd");
		return (chdir(home), 1);
	}
	printf("%s\n", cwd);
	return (0);
}
