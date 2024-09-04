/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:24:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/04 14:30:24 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool g_sigint = false;

/*Holds all relevant functions related to the lexing part.
  Inserts space before and after operants, expands $, splits
  input by words (if in unquoted passage) into 2d array.
  Assigns tokens to strings of 2d array and removes quotes
  from strings of 2d array*/
int	lexer(t_data *data)
{
	int	i;

	i = -1;
	if (data->err_flag)
		return (0);
	if (insert_space(data))
		return (1);
	if (ft_expand(data))
		return (1);
	if (check_pipes(data->input))
	{
		data->err_flag = 1;
		free_str(&data->input);
		return (0);
	}
	data->tokens = ft_tokenize(data->input);
	if (!data->tokens)
		return (1);
	if (!ft_malloc_token(data))
		return (1);
	while (i++, data->tokens[i])
		assign_token_type(data, i);
	if (remove_quotes(data))
		return (1);
	return (0);
}

/*Allocates sufficient memory for process structs and
  populats them with respective data. Also creates command
  path for later execution part and filenames for heredocs.*/
int	parsing(t_data *data)
{
	if (data->err_flag)
		return (0);
	if (init_proc_structs(data))
		return (1);
	if (init_path(data))
		return (1);
	if (alloc_here_filename(data))
		return (1);
	init_index(data);
	if (create_heredocs(data))
		return (1);
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
		{
			if (ft_strlen(data->input) > 0)
				add_history(data->input);
			if (not_valid_input(data->input, data))
			{
				free_str(&data->input);
				data->err_flag = 1;
			}
			if (lexer(data))
				free_all(data, 1);
			if (parsing(data))
				free_all(data, 1);
			if (exec_proc(data))
				free_all(data, 0);
			free_all(data, 0);
		}
	}
	return (0);
}

void	init_index(t_data *data)
{
	data->j = 0;
	data->i = 0;
	data->k = 0;
	data->l = 0;
	data->m = 0;
}

/*Initialise all relevant data of the main data struct*/
void	init_data(t_data *data)
{
	data->temp_env = NULL;
	data->tokens = NULL;
	data->input = NULL;
	data->token_list = NULL;
	data->proc = NULL;
	data->count_cmd = 0;
	data->num_tokens = 0;
	data->count_other = 0;
	data->proc_nbr = 0;
	data->err_flag = 0;
	data->path_arr = NULL;
	data->save_stdout = 0;
	data->save_stdin = 0;
	data->nl = "\n";
	data->return_val = 0;
	data->tmp = NULL;
	data->pid_arr = NULL;
	data->fd_arr = NULL;
	data->exit_status = 0;
	data->delim_fst_line = 0;
	data->exit_expand = 0;
	data->before = NULL;
	data->after = NULL;
	data->flag_before = 0;
	data->flag_after = 0;
	data->pipe_flag = 0;
	data->flag_cntlr_d = 0;
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
	return (0);
}
