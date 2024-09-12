/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:58:02 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/12 15:25:51 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns a string with the related expansion (text behind '= sign')
  of respective env. variable (tmp). Before compares to be expanded
  variable until '=' sign with respective env var.*/
char	*get_expansion(t_data *data, char *tmp)
{
	int	j;
	int	len;
	int	len2;

	j = 0;
	tmp = ft_ms_strjoin(tmp, "=");
	if (!tmp)
		return (NULL);
	len = ft_strlen(tmp);
	len2 = 0;
	while (data->temp_env[j])
	{
		if (ft_strncmp(data->temp_env[j], tmp, len) == 0)
		{
			free_str(&tmp);
			len2 = ft_strlen(data->temp_env[j]) - len;
			tmp = ft_substr(data->temp_env[j], len, len2);
			if (!tmp)
				return (NULL);
		}
		j++;
	}
	return (tmp);
}

/*Helper function of expand_or_cut_var function.
  Loops through env array and checks if identified 
  env var is present.*/
int	var_exist(t_data *data, char *tmp)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(tmp);
	while (data->temp_env[j])
	{
		if (ft_strncmp(data->temp_env[j], tmp, len) == 0)
			return (1);
		j++;
	}
	return (0);
}

/*Helper function of cut_var function, creates NULL-String
  in case cut out variable is only part of the string.*/
int	create_null_string(t_data *data)
{
	free_str(&data->input);
	data->input = ft_strdup("");
	data->err_flag = 1;
	if (!data->input)
		return (1);
	return (0);
}

/*Helper function of "check_before_after_case function"*/
static int	before_after_cut_var(t_data *data)
{
	if (!data->input)
		data->input = ft_strdup(data->before);
	if (!data->input)
		return (1);
	free_str(&data->before);
	data->input = ft_ms_strjoin_free_both(data->input, data->after);
	if (!data->input)
		return (1);
	return (0);
}

/*Helper function of cut_var, cuts out not found variable
  depending on where the variable is located in the string.*/
int	check_before_after_case(t_data *data)
{
	if (data->flag_before && data->flag_after)
	{
		if (before_after_cut_var(data))
			return (1);
	}
	else if (data->flag_before && !data->flag_after)
	{
		data->input = ft_strdup(data->before);
		if (!data->input)
			return (1);
		free_str(&data->before);
	}
	else if (!data->flag_before && data->flag_after)
	{
		data->input = ft_strdup(data->after);
		if (!data->input)
			return (1);
		free_str(&data->after);
	}
	return (0);
}
