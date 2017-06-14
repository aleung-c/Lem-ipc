/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:55:01 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/13 16:55:03 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

t_vec2					get_target(t_lemipc *lemipc)
{
	t_vec2		target;

	(void)lemipc;
	target.x = -1;
	target.y = -1;
	target = distance_search(lemipc);
	target.x += rand() % 1;
	target.y += rand() % 1;
	// printf("target at: %dx %dy\n", target.x, target.y);
	return (target);
}

/*
**	The simplest search method: i run through the map, and check the distance
**	from the enemy to the player. the closer one shall be my target to attack.
*/

t_vec2					distance_search(t_lemipc *lemipc)
{
	int			x;
	int			y;
	int			i;
	int			cur_value;
	int			min_dist;
	int			cur_dist;
	t_vec2		found_targets[SEARCH_SAMPLES];
	t_vec2		closest_target;

	x = 0;
	y = 0;
	i = 0;
	while (y != BOARD_HEIGHT)
	{
		while (x != BOARD_WIDTH)
		{
			cur_value = get_board_value(lemipc->map, x, y);
			if (cur_value != 0 && cur_value != lemipc->player.team)
			{
				found_targets[i].x = x;
				found_targets[i].y = y;
				i++;
				if (i == SEARCH_SAMPLES)
					break ;
			}
			x++;
		}
		y++;
		x = 0;
		if (i == SEARCH_SAMPLES)
			break ;
	}

	// now get the closest from the found targets
	x = 0;
	min_dist = BOARD_HEIGHT * BOARD_WIDTH;
	while (x != i)
	{
		cur_dist = get_distance(lemipc->player.pos, found_targets[x]);
		if (cur_dist < min_dist)
		{
			min_dist = cur_dist;
			closest_target = found_targets[x];
		}
		x++;
	}
	return (closest_target);
}




