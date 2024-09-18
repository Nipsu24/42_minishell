/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:11:07 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/18 13:43:11 by mmeier           ###   ########.fr       */
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
