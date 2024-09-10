/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:45:25 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/10 13:08:05 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to print an error message. If cmd is not NULL, print the command
   name. If str is not NULL, print the error message. */
void	print_error(char *cmd, char *str)
{
	if (cmd)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
	}
	if (str)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

/* Function to update the exit status. If cmd or msg is not NULL, print the
error message. Then update the exit status with the given status. */
int	update_exit_status(t_data *data, int status, char *cmd, char *msg)
{
	if (cmd || msg)
		print_error(cmd, msg);
	data->exit_status = status;
	return (status);
}

void	init_index(t_data *data)
{
	data->j = 0;
	data->i = 0;
	data->k = 0;
	data->l = 0;
	data->m = 0;
}

/*Holds all relevant functions related to the lexing part.
  Inserts space before and after operants, expands $, splits
  input by words (if in unquoted passage) into 2d array.
  Assigns tokens to strings of 2d array and removes quotes
  from strings of 2d array*/
int	lexer(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
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
	printf("INPUT: %s\n", data->input);
	data->tokens = ft_tokenize(data->input);
	if (!data->tokens)
		return (1);
	while(j++, data->tokens[j])
		printf("%s\n", data->tokens[j]);
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
