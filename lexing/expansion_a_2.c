/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_a_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:34:34 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/11 16:35:51 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Helper function of ft_expand, needed because of norm*/
void	helper_ft_expand(t_data *data, int *i)
{
	if (data->input[*i] != '$')
		(*i)++;
	if (data->input[*i] == '$' && between_quotes(data->input, *i) == 2)
		(*i)++;
}
