/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:24:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/15 16:21:28 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/*The 'readline' function enables writing commands to program during execution. 
  In case 'env' is typed to shell, env. variables are printed to the terminal, 
  otherwise command that user inputs is printed. The 'add_history' function enables 
  visibility of previous inserted commands (using keyboards "arrow up" after a command
  has been typed)*/
int	ft_input(char **env)
{
	char	*input;
	char	*environment = "env";

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("EOF or ERROR");
			return (1);
		}
		if (ft_strncmp(input, environment, 3) == 0)
			print_env(env);
		else
			printf("You entered %s\n", input);
		if (ft_strlen(input) > 0)
			add_history(input);
		free(input);
		input = NULL;
	}
	return (0);
}

/*String array 'env' holds by default environment variables of the system. Array
  still needs to be copied before doing any alterations, but it's already possible
  to print it. */
int	main(int ac, char *av[], char *env[])
{
	if (ac > 1 || av[1])
	{
		printf("Error. File does not take input.\n");
		return (1);
	}
	else
		ft_input(env);
	return (0);
}
