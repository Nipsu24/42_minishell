/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:15:44 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/05 21:35:52 by cesasanc         ###   ########.fr       */
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
void	print_echo(t_data *data)
{
	bool	n_flag;
	int		i;

	n_flag = false;
	i = 1;
	if (data->proc[data->j].cmd[1]
		&& is_newline(data->proc[data->j].cmd[1]))
	{
		n_flag = true;
		i++;
	}
	while (data->proc[data->j].cmd[i])
	{
		printf("%s", data->proc[data->j].cmd[i]);
		if (data->proc[data->j].cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}

/* The echo command. If there are no arguments, print a newline character.
If there are arguments, print them. */
int	echo(t_data *data)
{
	if (!(data->proc[data->j].cmd[1]))
	{
		printf("\n");
		free_arr(&data->proc[data->j].cmd);
		return (0);
	}
	print_echo(data);
	free_str(&data->proc[data->j].cmd[1]);
	return (0);
}
