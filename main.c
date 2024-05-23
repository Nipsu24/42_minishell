/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:24:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/23 11:55:36 by mmeier           ###   ########.fr       */
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

/*Frees relevant parts of the main struct. Last if-statement still
  to be investigated if sufficient.*/
void	free_all(t_data *data)
{
	int	j;

	j = 0;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens && data->tokens[j])
	{
		while (data->tokens[j])
		{
			free(data->tokens[j]);
			data->tokens[j] = NULL;
			j++;
		}
		free(data->tokens);
		data->tokens = NULL;
	}
	if (data->token_list)
	{
		free(data->token_list->entry);
		free(data->token_list);
		data->token_list = NULL;
	}
}

/*The 'readline' function enables writing commands to program during execution. 
  In case 'env' is typed to shell, env. variables are printed to the terminal, 
  otherwise command that user inputs is printed. The 'add_history' function 
  enables visibility of previous inserted commands (using keyboards "arrow up" 
  after a command has been typed)*/
static int	ft_input(t_data *data)
{
	char		*environment;
	int			i;

	i = 0;
	environment = "env";
	while (1)
	{
		data->input = readline("minishell> ");
		if (!data->input)
		{
			printf("EOF or ERROR");
			return (1);
		}
		if (ft_strncmp(data->input, environment, 3) == 0)
			print_env(data->temp_env);
		else
			printf("You entered %s\n", data->input);
		if (ft_strlen(data->input) > 0)
			add_history(data->input);
		data->tokens = ft_tokenize(data->input, ' ', '"');
		if (!data->tokens)
			return (1);
		if (!ft_malloc_token(data))
			return (1);
		while (data->tokens[i])
		{
			data->token_list->entry[i].cnt = data->tokens[i];
			ft_token_type(data, i);
			printf("%s\n", data->token_list->entry[i].cnt);
			printf("%d\n", data->token_list->entry[i].type);
			i++;
		}
		if (token_syntax_check(data))
			free_all(data);
		i = 0;
		free_all(data);
	}
	return (0);
}

/*String array 'env' holds by default environment variables of the system. 
  Array still needs to be copied before doing any alterations, but it's 
  already possible to print it.*/
int	main(int ac, char *av[], char *env[])
{
	t_data	data;	

	data.temp_env = env;
	if (ac > 1 || av[1])
	{
		printf("Error. File does not take input.\n");
		return (1);
	}
	else
		ft_input(&data);
	return (0);
}
