/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:24:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/06 11:48:31 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Holds all relevant functions related to the lexing part.
  Inserts space before and after operants, expands $, splits
  input by words (if in unquoted passage) into 2d array.
  Assigns tokens to strings of 2d array and removes quotes
  from strings of 2d array*/
int	lexer(t_data *data)
{
	int	i;

	i = 0;
	if (insert_space(data))
		return (1);
	if (ft_expand(data))
		return (1);
	data->tokens = ft_tokenize(data->input);
	if (!data->tokens)
		return (1);
	if (!ft_malloc_token(data))
		return (1);
	while (data->tokens[i])
	{
		assign_token_type(data, i);
		//printf("%s\n", data->tokens[i]);
		//printf("%d\n", data->token_list[i].type);
		i++;
	}
	if (remove_quotes(data))
		return (1);
	return (0);
}

/*Allocates sufficient memory for process structs and
  populats them with respective data. Also creates command
  path for later execution part.*/
int	parsing(t_data *data)
{
	if (init_proc_structs(data))
		return (1);
	if (init_path(data))
		return (1);
	return (0);
}

/*The 'readline' function enables writing commands to program during execution. 
  In case 'env' is typed to shell, env. variables are printed to the terminal, 
  otherwise command that user inputs is printed. The 'add_history' function 
  enables visibility of previous inserted commands (using keyboards "arrow up" 
  after a command has been typed). err_flag prevents going into further
  functions if not valid input is inserted (flag set to 1). In case any function
  in err_flag if statement fails, data is freed and exited (1), except when
  exec_proc fails (0/void)*/
static int	ft_input(t_data *data)
{
	char		*environment;

	environment = "env";
	while (1)
	{
		data->err_flag = 0;
		setup_signal();
		data->input = readline("minishell> ");
		if (!data->input)
		{
			printf("EOF or ERROR");
			return (1);
		}
		if (ft_strlen(data->input) > 0)
			add_history(data->input);
		if (not_valid_input(data->input))
		{
			free_str(&data->input);
			data->err_flag = 1;
		}
		if (data->err_flag == 0)
		{
			if (lexer(data))
				free_all(data, 1);
			if (ft_strncmp(data->input, environment, 3) == 0)
				print_env(data->temp_env);
			// else
			// 	printf("You entered %s\n", data->input);
			if (parsing(data))
				free_all(data, 1);
			count_heres(data);
			// if (exec_proc(data))
			// 	free_all(data, 0);
			free_all(data, 0); //needed here?
		}
	}
	return (0);
}

/*Initialise all relevant data of the main data struct*/
void	init_data(t_data *data)
{
	data->temp_env = NULL;
	data->tokens = NULL;
	data->input = NULL;
	data->token_list = NULL;
	data->count_cmd = 0;
	data->count_other = 0;
	data->proc_nbr = 0;
	data->err_flag = 0;
	data->path_arr = NULL;
	data->save_stdout = 0;
	data->save_stdin = 0;
	data->temp_here = NULL;
}

/*String array 'env' holds by default environment variables of the system. 
  Array is copied with ft_copy_env so that any alterations done to the
  env variables during minishell execution do not affect the original env.*/
int	main(int ac, char *av[], char *env[])
{
	t_data	data;	

	init_data(&data);
	data.temp_env = ft_copy_env(env, data.temp_env);
	if (!data.temp_env)
		return (1);
	if (ac > 1 || av[1])
	{
		printf("Error. File does not take input.\n");
		return (1);
	}
	else
		if (ft_input(&data))
			return (1);
	return (0);
}
