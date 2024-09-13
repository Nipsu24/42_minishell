/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:24:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/13 12:50:59 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_sigint = false;

/* Function to handle the input of the user. If the input is not valid, return 1
If the input is valid, call the lexer, parser and executor functions. */
static int	input_extra(t_data *data)
{
	if (ft_strlen(data->input) > 0)
		add_history(data->input);
	if (not_valid_input(data->input, data))
	{
		free_str(&data->input);
		data->err_flag = 1;
	}
	if (lexer(data))
		return (free_all(data, 0), 1);
	if (parsing(data))
		return (free_all(data, 0), 1);
	if (exec_proc(data))
		free_all(data, 0);
	free_all(data, 0);
	return (0);
}

/*The readline function enables writing commands to program 
  during execution. The 'add_history' function enables visibility
  of previous inserted commands(using keyboards "arrow up" after
  a command has been typed). err_flag prevents going into further
  functions if not valid input is inserted (flag set to 1).
  In case any function in err_flag if statement fails, data is
  freed and exited (1), except when exec_proc fails (0/void)*/
static int	ft_input(t_data *data)
{
	int	return_val;

	return_val = 0;
	while (1)
	{
		data->err_flag = 0;
		setup_signal();
		data->input = readline("minishell> ");
		if (!data->input)
		{
			write(STDERR_FILENO, "exit\n", 5);
			break ;
		}
		if (!data->input[0])
			free_str(&data->input);
		else
			return_val = input_extra(data);
		if (return_val)
		{
			free_arr(&data->temp_env);
			exit(data->exit_status);
		}
	}
	return (0);
}

/*Initialise all relevant arrays of the main data struct*/
void	init_arrays(t_data *data)
{
	data->temp_env = NULL;
	data->tokens = NULL;
	data->input = NULL;
	data->token_list = NULL;
	data->proc = NULL;
	data->path_arr = NULL;
	data->tmp = NULL;
	data->pid_arr = NULL;
	data->fd_arr = NULL;
	data->before = NULL;
	data->after = NULL;
}

/*Initialise all relevant data of the main data struct*/
void	init_data(t_data *data)
{
	init_arrays(data);
	data->count_cmd = 0;
	data->num_tokens = 0;
	data->count_other = 0;
	data->proc_nbr = 0;
	data->err_flag = 0;
	data->save_stdout = 0;
	data->save_stdin = 0;
	data->nl = "\n";
	data->return_val = 0;
	data->exit_status = 0;
	data->delim_fst_line = 0;
	data->exit_expand = 0;
	data->flag_before = 0;
	data->flag_after = 0;
	data->pipe_flag = 0;
	data->flag_cntlr_d = 0;
	data->sq = 0;
	data->dq = 0;
	data->first = 0;
	data->second = 0;
	init_index(data);
}

/*String array 'env' holds by default environment variables of the system. 
  Array is copied with ft_copy_env so that any alterations done to the
  env variables during minishell execution do not affect the original env.*/
int	main(int ac, char *av[], char *env[])
{
	t_data	data;	

	init_data(&data);
	data.temp_env = ft_copy_env(env, &data);
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
	free_arr(&data.temp_env);
	return (0);
}
