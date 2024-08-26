/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:50:44 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/26 15:18:11 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Allocates memory for later joining the different parts of the
  string. Only allocates memory for parts for which it is needed, 
  e.g. if to be expanded part is at the beginning of the string, 
  memory will only be allocated for part which comes after the 
  to be expanded part.*/
static int	malloc_before_after(t_data *data, int start, int len)
{
	int	len2;

	data->flag_before = 0;
	data->flag_after = 0;
	len2 = ft_strlen(data->input) - (start + len + 1);
	if (start)
	{
		data->before = ft_substr(data->input, 0, start);
		if (!data->before)
			return (1);
		data->flag_before = 1;
	}
	if (data->input[start + len + 1])
	{
		data->after = ft_substr(data->input, start + len + 1, len2);
		if (!data->after)
			return (1);
		data->flag_after = 1;
	}
	free_str(&data->input);
	return (0);
}

/*Handles use case where only the to be expanded variable is
  in between of characters in the string*/
static int	join_before_after(t_data *data, char *exp_var)
{
	if (!data->input)
	{
		data->input = ft_strdup(data->before);
		if (!data->input)
			return (1);
	}
	free_str(&data->before);
	data->input = ft_ms_strjoin_free_both(data->input, exp_var);
	if (!data->input)
		return (1);
	data->input = ft_ms_strjoin_free_both(data->input, data->after);
	if (!data->input)
		return (1);
	return (0);
}

/*Handles use case wheere only the to be expanded variable is
  part of the string*/
static int	only_exp_var_in_str(t_data *data, char *exp_var)
{
	data->input = ft_strdup(exp_var);
	if (!data->input)
		return (1);
	free_str(&exp_var);
	return (0);
}

/*Cuts input string into before and after parts of the expanded part, then
  rejoins all parts (incl. expanded part). Certain if conditions in place
  in order to only allocate memory for before and after part if needed. */
int	incl_exp_var(t_data *data, int start, char *exp_var, int len)
{
	if (malloc_before_after(data, start, len))
		return (1);
	if (data->flag_before && !data->flag_after)
	{
		data->input = ft_ms_strjoin_free_both(data->before, exp_var);
		if (!data->input)
			return (1);
	}
	else if (data->flag_after && !data->flag_before)
	{
		data->input = ft_ms_strjoin_free_both(exp_var, data->after);
		if (!data->input)
			return (1);
	}
	else if (data->flag_after && data->flag_before)
	{
		if (join_before_after(data, exp_var))
			return (1);
	}
	else if (!data->flag_after && !data->flag_before)
	{
		if (only_exp_var_in_str(data, exp_var))
			return (1);
	}
	return (0);
}

/*Cuts out not found $-variable of input string. Certain if conditions in 
  place in order to only allocate memory for before and after part if
  needed. Creates Null-String in case cut out part is only part in the
  string.*/
int	cut_var(t_data *data, int start, int len)
{
	int		len2;

	len2 = ft_strlen(data->input) - (start + len + 1);
	if (start == 0 && len2 == 0)
	{
		if (create_null_string(data))
			return (1);
		else
			return (0);
	}
	if (malloc_before_after(data, start, len))
		return (1);
	if (check_before_after_case(data))
		return (1);
	return (0);
}
