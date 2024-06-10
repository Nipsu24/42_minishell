/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:46:06 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/06/06 17:46:08 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Counts and returns amount of | which are not in quotes*/
static int	ft_pipe_count(char *s)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (s[i])
	{
		if (s[i] == '|' && !between_quotes(s, i))
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

/*Returns " or ' character in case c is one of these, otherwise 0*/
static int is_quote(char c)
{
    return (c == '"' || c == '\'');
}

/*Helper function of ft_split_prcs. Quote != 0 means, that character 
  is in quoted segment. If not in quoted segment and character is pipe
  iteration stops and index i is used in split_prcs function for sub-
  string function.*/
static void is_in_quotes(char *s, size_t *i)
{
	char quote = 0;

	while (s[*i] && (s[*i] != '|' || quote != 0))	
	{
		if (is_quote(s[*i]))
		{
			if (quote == s[*i])
				quote = 0;
			else if (quote == 0)
				quote = s[*i];
		}
		(*i)++;
	}
}

/*Fills initialised strings of 2d array with characters excluding pipe
  character*/
static char **ft_fill_prcs(char *s, char **strings)
{
    size_t start;
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    start = 0;
    while (s[i])
    {
        if (s[i] && s[i] != '|')
        {
            start = i;
			is_in_quotes(s, &i);
            strings[j] = ft_substr(s, start, (i - start));
            if (strings[j] == 0)
                return (ft_free(strings, j));
            j++;
        }
        else
            (i)++;
    }
    strings[j] = 0;
    return (strings);
}

/*function splits user input in 2d array depending on how many pipes input contains.
  +2 in order to account for Null-Terminator and correct amount of strings (e.g.
  pipe_count = 1 means that 2 strings need to be created)*/
static char	**ft_split_pipes(char *s)
{
	char	**strings;

	if (!s)
		return (0);
	strings = (char **) malloc (sizeof(char *) * (ft_pipe_count(s) + 2));
	if (strings == 0 || s == 0)
		return (NULL);
	return (ft_fill_prcs(s, strings));
}

/*Initiates and fills process array in case there is no pipe present
  in the user input.*/
static int init_prc_arr(t_data *data)
{
	data->prcs = (char **) malloc (sizeof(char *) + 1);
	if (!data->prcs)
		return (1);
	data->prcs[0] = ft_strdup(data->input);
	if (!data->prcs[0])
		return (1);
	data->prcs[1] = 0;
	return (0);
}

/*Trims result of split processes by pipes from free spaces*/
static int	init_trim(t_data *data)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (data->prcs_buf[j])
		j++;
	data->prcs = (char **) malloc (sizeof(char *) * (j + 1));
	if (!data->prcs)
		return (1);
	while (data->prcs_buf[i])
	{
		data->prcs[i] = ft_strtrim(data->prcs_buf[i], " ");
		if (data->prcs[i] == 0)
		{
			(ft_free(data->prcs, i));
			return (0);
		}
		i++;
	}
	data->prcs[i] = 0;
	free_arr(data->prcs_buf);
	return (0);
}

/*Splits input into processes (identified by pipes). If no pipe present, 
  input will be nevertheless stored in 2d array in order to ensure same 
  data structure as for input that contains pipes.*/
int split_in_prcs(t_data *data)
{
	int	j;

	j = 0;
	data->pipe_count = ft_pipe_count(data->input);
	if (!data->pipe_count)
	{
		if (init_prc_arr(data))
			return (1);
	}
	else
	{
		data->prcs_buf = ft_split_pipes(data->input);
		if (!data->prcs_buf)
			return (1);
		if (init_trim(data))
			return (1);
	}
	while (data->prcs[j])
	{
		printf("%s\n", data->prcs[j]);
		j++;
	}
	return (0);
}


