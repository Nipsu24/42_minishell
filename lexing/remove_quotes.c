/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:07:00 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/09/11 16:24:33 by mmeier           ###   ########.fr       */
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

static int	remove_quotes_str(t_data *data, int j)
{
	int		i;
	char	quote;
	int		first;
	int		second;

	i = 0;
	first = -1;
	second = -1;
	quote = 'a';
	while (data->tokens[j][i])
	{
		if (data->tokens[j][i] == '"' || data->tokens[j][i] == '\'')
		{
			quote = data->tokens[j][i];
			first = i;
			i++;
			while (data->tokens[j][i])
			{
				if (quote == data->tokens[j][i])
				{
					second = i;
					break ;
				}
				i++;
			}
			if (first >= 0 && second >= 0)
			{
				if (cut_quotes_str(data, j, first, second))
					return (1);
				first = -1;
				second = -1;
				i = 0;
			}
		}
		else
			i++;
	}
	return (0);
}

int	remove_quotes(t_data *data)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = NULL;
	while (data->tokens[j])
	{
		if (remove_quotes_str(data, j))
			return (1);
		j++;
	}
	return (0);
}
