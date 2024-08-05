/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:15:44 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/05 13:20:19 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if the argument is the -n flag. */
static bool	is_newline(const char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args[1] && is_newline(args[1]))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!n_flag)
		ft_printf("\n");
	return (0);
}
