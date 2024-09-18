/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_a_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:38:46 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/18 11:52:48 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Converts int exit_status to *char and stores it
  in exit_nbr variable.*/
static char	*expand_exit_status(t_data *data)
{
	char	*exit_nbr;

	exit_nbr = ft_itoa(data->exit_status);
	if (!exit_nbr)
		return (NULL);
	return (exit_nbr);
}

/*Checks characters after $-sign. If character is'?', exit status is 
  stored in tmp. Otherwise loops through string until space, " or 
  other $ and stores the part which needs to be expanded in tmp 
  variable.*/
static char	*get_tmp_var(t_data *data, int *i, int *len, int start)
{
	char	*tmp;

	tmp = NULL;
	if (data->input[*i] == '?')
	{
		tmp = expand_exit_status(data);
		if (!tmp)
			return (NULL);
		data->exit_expand = 1;
	}
	else
	{
		while (data->input[*i] && data->input[*i] != 32
			&& data->input[*i] != '"' && data->input[*i] != '$')
		{
			(*i)++;
			(*len)++;
		}
		tmp = ft_substr(data->input, start, *len);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

/*Checks if env variable exists and stores the expansion in tmp.
  Same function incl_exp_var is used for handling inserting the
  expanded part for both env var and exit_status. If env var does
  not exists and the expanded part is not an exit_status, string
  part after $-sign (including $-sign) gets cut out via cut_var.*/
static int	expand_or_cut_var(t_data *data, char *tmp, int start, int len)
{
	if (var_exist(data, tmp) && !data->exit_expand)
	{
		tmp = get_expansion(data, tmp);
		if (!tmp)
			return (1);
		if (incl_exp_var(data, start - 1, tmp, len))
			return (1);
	}
	else if (data->exit_expand)
	{
		if (incl_exp_var(data, start - 1, tmp, 1))
			return (1);
	}
	else
	{
		if (cut_var(data, start - 1, len))
		{
			free_str(&tmp);
			return (1);
		}
		free_str(&tmp);
	}
	return (0);
}

/*Identifies characters behind $-sign via get_tmp_var function and stores 
  them in tmp variable in order to further check if the value can be found
  within the env variabes or if it needs to be expanded to the exit_status.
  Further processing of expansion in expand_or_cut_var.*/
static int	def_var(t_data *data, int i)
{
	int		start;
	int		len;
	char	*tmp;

	start = i + 1;
	len = 0;
	tmp = NULL;
	i++;
	data->exit_expand = 0;
	tmp = get_tmp_var(data, &i, &len, start);
	if (!tmp)
		return (1);
	if (expand_or_cut_var(data, tmp, start, len))
		return (1);
	return (0);
}

/*Checks if $ is between quotes. If it is between double quotes or
  if it is not between any quotes, then data is passed to def_var for
  further processing.*/
int	ft_expand(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '$' && (!between_quotes(data->input, i)
				|| between_quotes(data->input, i) == 1)
			&& in_both_quotes(data->input, i) != 2)
		{
			if (data->input[i + 1] != 32 && data->input[i + 1] != '"'
				&& data->input[i + 1])
			{
				if (def_var(data, i))
					return (1);
				i = 0;
			}
			else
				i++;
		}
		if (!data->input || data->input[0] == '\0')
			break ;
		helper_ft_expand(data, &i);
	}
	return (0);
}
