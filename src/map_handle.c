/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 14:21:30 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/13 14:21:34 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

/*
**	Init the map and clears it with zeros.
*/

void	init_game(t_lemipc *lemipc)
{
	// Creates the segment.
	init_shm_segment(lemipc);
	
	clear_map(lemipc->map);

	init_semaphores(lemipc);
	
	init_msgq(lemipc);
}

/*
**	Clears the map with zeros.
*/

void			clear_map(int *map)
{
	int i;
	int end;

	i = 0;
	end = BOARD_HEIGHT * BOARD_WIDTH;
	while (i != end)
	{
		map[i] = 0;
		i++;
	}
}
