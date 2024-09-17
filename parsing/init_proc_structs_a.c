/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_proc_structs_a.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:28:18 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/17 16:35:12 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Initialised process structs by allocating memory and populating
  respective arrays etc. in each process struct.*/
int	init_proc_structs(t_data *data)
{
	if (count_pipes(data))
		return (1);
	if (data->err_flag)
		return (0);
	data->j = 0;
	if (alloc_proc_structs(data))
		return (1);
	if (fill_proc_structs(data))
		return (1);
	return (0);
}
