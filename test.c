/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:24:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/14 11:28:18 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_input(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("EOF or ERROR");
			return (1);
		}
		printf("You entered %s\n", input);
		free(input);
		input = NULL;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	if (ac > 1 || av[1])
		return (1);
	else
		if (ft_input())
			return (1);
	return (0);
}
