/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:45:25 by cesasanc          #+#    #+#             */
/*   Updated: 2024/09/16 16:04:24 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Helper function for lexer (needed for norm reasons)*/
static void	helper_lexer(t_data *data)
{
	int	i;

	i = -1;
	while (i++, data->tokens[i])
		assign_token_type(data, i);
}

/*Holds all relevant functions related to the lexing part.
  Inserts space before and after operants, expands $, splits
  input by words (if in unquoted passage) into 2d array.
  Assigns tokens to strings of 2d array and removes quotes
  from strings of 2d array*/
int	lexer(t_data *data)
{
	if (data->err_flag)
		return (0);
	if (insert_space(data))
		return (1);
	if (ft_expand(data))
		return (1);
	if (data->err_flag)
		return (0);
	if (check_pipes(data->input) || check_redirects(data->input))
	{
		data->err_flag = 1;
		return (0);
	}
	data->tokens = ft_tokenize(data->input, data);
	if (!data->tokens)
		return (1);
	if (!ft_malloc_token(data))
		return (1);
	helper_lexer(data);
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
