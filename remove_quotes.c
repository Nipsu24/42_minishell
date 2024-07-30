/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:07:00 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/07/29 14:07:03 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (0);
}
