/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:11:07 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/26 20:00:02 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints the current working directory */
int	pwd(void)
{
	char	cwd[BUFF_SIZE];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("Error getting cwd, or cwd is too long");
		return (1);
	}
	return (0);
}
