/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:15:44 by cesasanc          #+#    #+#             */
/*   Updated: 2024/08/06 11:42:34 by cesasanc         ###   ########.fr       */
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

/* Prints the arguments given to the echo command. If the -n flag is given,
the newline character is not printed. */
void	print_echo(char **args)
{
	bool	n_flag;
	int		i;

	n_flag = false;
	i = 1;
	if (args[1] && is_newline(args[1]))
	{
		n_flag = true;
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
}

/* The echo command. */
int	echo(char **args)
{
	if (!args[1])
	{
		ft_printf("\n");
		free_str(args);
		return (0);
	}
	print_echo(args);
	free_str(args);
	return (0);
}
