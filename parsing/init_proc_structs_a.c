/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_proc_structs_a.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:28:18 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/27 15:57:14 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Initialised process structs by allocating memory and populating
  respective arrays etc. in each process struct.*/
int	init_proc_structs(t_data *data)
{
	if (count_pipes(data))
		return (1);
	if (alloc_proc_structs(data))
		return (1);
	if (fill_proc_structs(data))
		return (1);
	return (0);
}