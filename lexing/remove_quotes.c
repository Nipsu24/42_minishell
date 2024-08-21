/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:07:00 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/08/21 10:49:58 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Helper function of remove_quotes_inside, populates previously memory allocated
  strings with characters of original strings except if they are single or
  double quotes.*/
static int	create_str_w_o_quotations(t_data *data, char *tmp, int count)
{
	tmp = malloc(sizeof(char) * (ft_strlen(data->tokens[data->j]) - count + 1));
	if (!tmp)
		return (1);
	data->i = 0;
	data->k = 0;
	while (data->tokens[data->j][data->i])
	{
		if (data->tokens[data->j][data->i] != '"'
			&& data->tokens[data->j][data->i] != '\'')
			tmp[data->k++] = data->tokens[data->j][data->i];
		data->i++;
	}
	tmp[data->k] = '\0';
	free_str(&data->tokens[data->j]);
	data->tokens[data->j] = tmp;
	return (0);
}

/*Counts amount of quotation marks remaining in the strings of the 2d array and 
  substracts this amount from the respective string lenghts in order to allocate
  memory for strings where these quotation marks are 'cut out'.*/
static int	remove_quotes_inside(t_data *data)
{
	char	*tmp;
	int		count;

	count = 0;
	init_index(data);
	while (data->tokens[data->j])
	{
		tmp = NULL;
		count = 0;
		data->i = 0;
		while (data->tokens[data->j][data->i])
		{
			if (data->tokens[data->j][data->i] == '"'
				|| data->tokens[data->j][data->i] == '\'')
				count++;
			data->i++;
		}
		if (count)
		{
			if (create_str_w_o_quotations(data, tmp, count))
				return (1);
		}
		data->j++;
	}
	return (0);
}

/*Helper function of remove_quotes, removes double quotes from
  beginning and end of data->tokens strings.*/
static int	trim_double_quotes(t_data *data, char *tmp, int *j)
{
	tmp = ft_strtrim(data->tokens[*j], "\"");
	if (!tmp)
		return (1);
	free(data->tokens[*j]);
	data->tokens[*j] = NULL;
	data->tokens[*j] = tmp;
	return (0);
}

/*Helper function of remove_quotes, removes single quotes from
  beginning and end of data->tokens strings.*/
static int	trim_single_quotes(t_data *data, char *tmp, int *j)
{
	tmp = ft_strtrim(data->tokens[*j], "\'");
	if (!tmp)
		return (1);
	free(data->tokens[*j]);
	data->tokens[*j] = NULL;
	data->tokens[*j] = tmp;
	return (0);
}

/*Removes single and double quotes of beginning and end ofdata->tokens strings.
  Double or single quotes which are next to each other (e.g. "") are excluded 
  from this operation.*/
int	remove_quotes(t_data *data)
{
	int		j;
	int		i;
	char	*tmp;

	j = 0;
	i = 0;
	tmp = NULL;
	while (data->tokens[j])
	{
		tmp = NULL;
		if (data->tokens[j][i] == '"' && data->tokens[j][i + 1] != '"')
		{
			if (trim_double_quotes(data, tmp, &j))
				return (1);
		}
		if (data->tokens[j][i] == '\'' && data->tokens[j][i + 1] != '\'')
		{
			if (trim_single_quotes(data, tmp, &j))
				return (1);
		}
		j++;
	}
	if (remove_quotes_inside(data))
		return (1);
	return (0);
}
