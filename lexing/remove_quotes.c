/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:07:00 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/09/17 15:09:40 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_quotes_in_str(t_data *data, int j, char *tmp)
{
	tmp = ft_strdup("");
	if (!tmp)
		return (1);
	free_str(&data->tokens[j]);
	data->tokens[j] = tmp;
	return (0);
}

/*Checks first if string only contains 2 matching quotes and nothing apart
  from it. In this case creates empty string with ft_strdup. Otherwise 
  allocates memory for newly created string where the 2 matching quotes
  are cut out.*/
static int	cut_quotes_str(t_data *data, int j, int first, int second)
{
	char	*tmp;

	data->i = 0;
	data->k = 0;
	tmp = NULL;
	if (ft_strlen(data->tokens[j]) == 2)
	{
		if (only_quotes_in_str(data, j, tmp))
			return (1);
		else
			return (0);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(data->tokens[j]) - 2 + 1));
	if (!tmp)
		return (1);
	while (data->tokens[j][data->i])
	{
		if (data->i != first && data->i != second)
			tmp[data->k++] = data->tokens[j][data->i];
		data->i++;
	}
	tmp[data->k] = '\0';
	free_str(&data->tokens[j]);
	data->tokens[j] = tmp;
	return (0);
}

/*Assigns i value to first in second if 2 matching quotes are found.
  Then passes the string to cut_quotes function to create a new
  string without these matching quotes.*/
static int	helper_remove_quotes(t_data *data, int j, char quote)
{
	quote = data->tokens[j][data->i];
	data->first = data->i;
	data->i++;
	while (data->tokens[j][data->i])
	{
		if (quote == data->tokens[j][data->i])
		{
			data->second = data->i;
			break ;
		}
		data->i++;
	}
	if (data->first >= 0 && data->second >= 0)
	{
		if (cut_quotes_str(data, j, data->first, data->second))
			return (1);
		data->i = data->second - 1;
		data->first = -1;
		data->second = -1;
		// if (data->tokens[j][data->i])
		// 	data->i++;
		//data->i = 0;
	}
	return (0);
}

/*Checks if double or single quotes are present in the respective token.
  If yes, passes data to helper function in order to check if there are
  matching quotes for cutting those out.*/
static int	remove_quotes_str(t_data *data, int j)
{
	char	quote;

	data->i = 0;
	data->first = -1;
	data->second = -1;
	quote = 'a';
	while (data->tokens[j][data->i])
	{
		if (data->tokens[j][data->i] == '"' || data->tokens[j][data->i] == '\'')
		{
			if (helper_remove_quotes(data, j, quote))
				return (1);
		}
		else
			data->i++;
	}
	return (0);
}

/*Removes matching single or double quotes from each token*/
int	remove_quotes(t_data *data)
{
	int		j;

	j = 0;
	while (data->tokens[j])
	{
		if (remove_quotes_str(data, j))
			return (1);
		j++;
	}
	return (0);
}
