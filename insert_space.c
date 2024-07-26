/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:29:37 by mmeier            #+#    #+#             */
/*   Updated: 2024/07/22 13:00:22 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Counts amount of operants in the input string. Operants
  in quotations are not counted.*/
static int	count_op(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->input[i])
	{
		if ((data->input[i] == '<'
			|| data->input[i] == '>'
			|| data->input[i] == '|') 
			&& !between_quotes(data->input, i)
			&& data->input[i + 1] != '<'
			&& data->input[i + 1] != '>')
			count++;
		i++;
	}
	printf("AMOUNT OP is: %d\n", count);
	return (count);
}

/*Allocates memory based on lenght of input string and
  amount of operants. Goal is to insert before and after
  each operant a space (independent if there is already
  a space or not). Therefore, count of operants is multi-
  plied by 2, + 1 for NULL terminator.*/
static char	*malloc_for_spaces(t_data *data, int count)
{
    char *ptr;

    ptr = malloc(ft_strlen(data->input) + count * 2 + 1);
    if (!ptr)
        return (NULL);
	return (ptr);
}

/*Inserts space before and after each operant which is not
  in quotes. ptr[j++] at first assigns value to ptr[j] and
  afterwards increments ptr's index*/
static char	*fill_str_w_spaces(t_data *data, char *ptr)
{
    int	i;
    int	j;

	i = 0;
	j = 0;
    while (data->input[i])
	{
        if ((data->input[i] == '<' || data->input[i] == '>'
			|| data->input[i] == '|') && !between_quotes(data->input, i))
		{
            ptr[j++] = ' ';
            ptr[j++] = data->input[i];
            if (data->input[i + 1] == data->input[i])
                ptr[j++] = data->input[i++];
			ptr[j++] = ' ';
        }
		else
			ptr[j++] = data->input[i];
        i++;
    }
    ptr[j] = '\0';
    return (ptr);
}

/*Copies the newly allocated string with the inserted spaces
  to the initial data->input string*/
static int	copy_to_input(t_data *data, char *ptr)
{
	free(data->input);
	data->input = NULL;
	data->input = ptr;
	printf("NEW STRING: %s\n", data->input);
	return (0);
}

int	insert_space(t_data *data)
{
	int	count;
	char *ptr;

	count = count_op(data);
	if (count == 0)
		return (0);
	ptr = malloc_for_spaces(data, count);
	if (!ptr)
		return (1);
	ptr = fill_str_w_spaces(data, ptr);
	copy_to_input(data, ptr);
	return (0);
}
