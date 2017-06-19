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

t_vec2		get_target(t_lemipc *lemipc)
{
	t_vec2		target;

	target.x = -1;
	target.y = -1;
	target = distance_search(lemipc);
	target.x += rand() % 1;
	target.y += rand() % 1;
	return (target);
}

/*
**	The simplest search method: i run through the map, and check the distance
**	from the enemy to the player. the closer one shall be my target to attack.
*/

t_vec2		distance_search(t_lemipc *lemipc)
{
	int			i;
	t_vec2		found_targets[SEARCH_SAMPLES];

	i = stock_targets(lemipc, &found_targets[0], 0, 0);
	return (get_closest_target(lemipc, found_targets, i));
}

/*
**	In here, ill stock the all viables targets for the player,
**	but no more than SEARCH_SAMPLES value. We dont need all
**	targets.
*/

int			stock_targets(t_lemipc *lemipc, t_vec2 *found_targets, int x, int y)
{
	int			i;
	int			cur_value;

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
	return (i);
}

/*
**	For each previously stocked target, ill extract the closest one.
*/

t_vec2		get_closest_target(t_lemipc *lemipc, t_vec2 *found_targets, int i)
{
	int			x;
	int			min_dist;
	int			cur_dist;
	t_vec2		closest_target;

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

/*
**	This one is used for when I receive a message that
**	require assistance ==> parse the msg and create a position.
**
**	However, if the sender is myself(read too fast), I send the
**	msg back on te msg queue.
*/

t_vec2		set_target_from_msg(t_lemipc *lemipc, char *msg)
{
	t_vec2		ret;
	int			msg_sender;

	ret.x = -1;
	ret.y = -1;
	msg_sender = ft_atoi(msg);
	if (msg_sender == lemipc->player.nb)
	{
		send_msg_to_team(lemipc, msg);
		msg = NULL;
		return (ret);
	}
	parse_target_msg(msg, &ret);
	return (ret);
}
