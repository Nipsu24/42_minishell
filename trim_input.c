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

int	trim_space(t_data *data)
{
	char	*tmp;

	tmp = ft_strtrim(data->input, " ");
	if (!tmp)
		return (1);
	free(data->input);
	data->input = NULL;
	data->input = tmp;
	return (0);
}
