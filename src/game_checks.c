/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 13:09:02 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/13 13:09:04 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

int			is_point_in(t_lemipc *lemipc, t_vec2 point)
{
	(void)lemipc;
	if (point.x >= BOARD_WIDTH || point.x < 0
		|| point.y >= BOARD_HEIGHT || point.y < 0)
	{
		return (B_FALSE);
	}
	else
	{
		return (B_TRUE);
	}

}

/*
**	Check 8 directions around the player.
**	If there are two players from the same team that is not
**	the cur player team ==> death.
**
**	x means out of board in the scooped points.
*/

int			check_death(t_lemipc *lemipc)
{
	int			i;
	int			y;
	t_vec2		next_point;
	int			points[8];

	i = 8;
	next_point.x = lemipc->player.pos.x - 1;
	next_point.y = lemipc->player.pos.y + 1;
	// get the values on the 8 points surrounding the player.
	while (i != -1)
	{
		if (is_point_in(lemipc, next_point))
			points[i] = get_board_value(lemipc->map, next_point.x, next_point.y);
		else
			points[i] = 'x';
		next_point.x += 1;
		if (i % 3 == 0)
		{
			next_point.x -= 3;
			next_point.y -= 1;
		}
		i--;
	}
	// then check the value of these points.
	i = 0;
	y = 0;
	while (i != 8)
	{
		if (points[i] != (48 + lemipc->player.team))
		{
			while (y != 8)
			{
				if (points[y] == points[i] && (y != i))
					return (B_TRUE);
				y++;
			}
		}
		i++;
	}
	return (B_FALSE);
}
