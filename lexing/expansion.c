/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:38:46 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/20 15:18:13 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Loops through env array and checks if identified env var is
  present.*/
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

/*Returns a string with the related expansion (text behind '= sign')
  of respective env. variable (tmp). len++ to account for '='.*/
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
			free_str(&tmp);
			len2 = ft_strlen(data->temp_env[j]) - len;
			tmp = ft_substr(data->temp_env[j], len, len2);
			//printf("EXPANDED VAR IS:\n%s\n", tmp);
		}
		j++;
	}
	return (tmp);
}

/*Cuts input string into before and after parts of the expanded part, then
  rejoins all parts (incl. expanded part). Certain if conditions in place
  in order to only allocate memory for before and after part if needed. */
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
	if (data->input[start + len + 1])
		after = ft_substr(data->input, start + len + 1, len2);
	free_str(&data->input);
	if (before && !after)
		data->input = ft_ms_strjoin_free_both(before, exp_var);
	if (after && !before)
		data->input = ft_ms_strjoin_free_both(exp_var, after);
	if (after && before)
	{
		if (!data->input)
			data->input = ft_strdup(before);
		free_str(&before);
		data->input = ft_ms_strjoin_free_both(data->input, exp_var);
		data->input = ft_ms_strjoin_free_both(data->input, after);
	}
	if (!after && !before)
	{
		data->input = ft_strdup(exp_var);
		free_str(&exp_var);
	}
	//printf("NEW EXPANDED COMMAND is:\n%s\n", data->input);
}

/*Cuts out not found $-variable of input string. Certain if conditions in 
  place in order to only allocate memory for before and after part if
  needed.*/
static void	cut_var(t_data *data, int start, int len)
{
	char	*before;
	char	*after;
	int		len2;

	before = NULL;
	after = NULL;
	len2 = ft_strlen(data->input) - (start + len + 1);
	if (start == 0 && len2 == 0)
	{
		free_str(&data->input);
		data->input = ft_strdup("");
		//printf("TEST FOR DUP\n");
		return ;
	}
	if (start)
		before = ft_substr(data->input, 0, start);
	if (data->input[start + len + 1])
		after = ft_substr(data->input, start + len + 1, len2);
	free_str(&data->input);
	if (before && after)
	{
		if (!data->input)
			data->input = ft_strdup(before);
		free_str(&before);
		data->input = ft_ms_strjoin_free_both(data->input, after);
	}
	else if (before && !after)
	{
		data->input = ft_strdup(before);
		free_str(&before);
	}
	else if (!before && after)
	{
		data->input = ft_strdup(after);
		free_str(&after);
	}	
	//printf("NEW CUT EXPANDED COMMAND is: %s\n", data->input);
}

/*Identifies characters behind $-sign and stores them in tmp variable in
  order to further check if the value can be found within the env variabes (stops
  at null-terminator, space or quotes).
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
	while (data->input[i] && data->input[i] != 32 && data->input[i] != '"'
		&& data->input[i] != '$')
	{
		i++;
		len++;
	}
	tmp = ft_substr(data->input, start, len);
	if (var_exist(data, tmp))
	{
		//printf("VAR %s EXISTS\n", tmp);
		tmp = get_expansion(data, tmp);
		incl_exp_var(data, start - 1, tmp, len);
	}
	else
	{
		cut_var(data, start - 1, len);
		//printf("ENVAR-VAR %s\n", tmp); //new
		free_str(&tmp); //new
	}
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
			//printf("$ is between double quotes or no quotes\n");
			def_var(data, i);
			i = 0;
		}
		if (!data->input || data->input[0] == '\0')
			break ;
		i++;
	}
	//printf("FINAL STRING:\n%s000\n", data->input);
	return (0);
}
