/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:38:46 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/16 12:33:32 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_exist(t_data *data, char *tmp)
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

/*Returns a string with the related expansion (text behin '= sign')
  of respective env. variable (tmp)*/
static char	*get_expansion(t_data *data, char *tmp)
{
	int	j;
	int	len;
	int	len2;

	j = 0;
	len = ft_strlen(tmp);
	len2 = 0;
	while (data->temp_env[j])
	{
		if (ft_strncmp(data->temp_env[j], tmp, len) == 0)
		{
			len++;
			ft_free(&tmp);
			len2 = ft_strlen(data->temp_env[j]) - len;
			tmp = ft_substr(data->temp_env[j], len, len2);
			printf("EXPANDED VAR IS:\n%s\n", tmp);
		}
		j++;
	}
	return (tmp);
}

/*Cuts input string into before and after parts of the expanded part, then
  rejoins all parts (incl. expanded part)*/
static void	incl_exp_var(t_data *data, int start, char *exp_var, int len)
{
	char	*before;
	char	*after;
	int		len2;

	before = NULL;
	after = NULL;
	len2 = ft_strlen(data->input) - (start + len + 1);
	if (start)
		before = ft_substr(data->input, 0, start);
	if (data->input[len + 1]) 
		after = ft_substr(data->input, start + len + 1, len2);
	ft_free(&data->input);
	if (before)
		data->input = ft_strjoin(before, exp_var);
	if (after)
		data->input = ft_strjoin(data->input, after);
	else
		data->input = ft_strdup(exp_var);
	printf("NEW EXPANDED COMMAND is:\n%s\n", data->input);
}

/*Cuts out not found $-variable of input string*/
static void	cut_var(t_data *data, int start, int len)
{
	char	*before;
	char	*after;
	int		len2;

	len2 = ft_strlen(data->input) - start + len + 1;
	before = ft_substr(data->input, 0, start - 1);
	after = ft_substr(data->input, start + len + 1, len2);
	free(data->input);
	data->input = NULL;
	data->input = ft_strjoin(before, after);
	printf("NEW CUT EXPANDED COMMAND is: %s\n", data->input);
}

/*Identifies characters behind $-sign and stores them in tmp variable in
  order to further check if the value can be found within the env variabes.
  If it can be found, value gets expanded via incl_exp_var function, otherwise 
  it gets cut out of string with cut_var function.*/
static void	def_var(t_data *data, int i)
{
	int		start;
	int		len;
	char	*tmp;

	start = i + 1;
	len = 0;
	i++;
	tmp = NULL;
	while (data->input[i] && data->input[i] != 32 && data->input[i] != '"')
	{
		i++;
		len++;
	}
	tmp = ft_substr(data->input, start, len);
	if (var_exist(data, tmp))
	{
		printf("VAR %s EXISTS\n", tmp);
		tmp = get_expansion(data, tmp);
		incl_exp_var(data, start - 1, tmp, len);
	}
	else
		cut_var(data, start - 1, len);
	printf("ENVAR-VAR %s\n", tmp);
	free(tmp);
	tmp = NULL;
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
				|| between_quotes(data->input, i) == 1))
		{
			printf("$ is between double quotes or no quotes\n");
			def_var(data, i);
		}
		i++;
	}
	return (0);
}
