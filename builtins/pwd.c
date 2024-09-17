/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:11:07 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/17 17:38:06 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints the current working directory */
int	pwd(t_data *data)
{
	char	cwd[BUFF_SIZE];
	
	if (!getcwd(cwd, sizeof(cwd)))
	{
		update_exit_status(data, 1, "pwd", "Error getting cwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
