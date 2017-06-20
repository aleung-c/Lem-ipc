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

/*
**	Check 8 directions around the player.
**	If there are two players from the same team that is not
**	the cur player team ==> death.
**
**	-1 means out of board in the scooped points.
*/

int			am_i_dead(t_lemipc *lemipc)
{
	int			points[9];

	get_values_around(lemipc, &points[0]);
	return (check_values_around(lemipc, &points[0]));
}

void		get_values_around(t_lemipc *lemipc, int *points)
{
	int			i;
	int			y;
	t_vec2		next_point;

	i = 8;
	y = 0;
	next_point.x = lemipc->player.pos.x - 1;
	next_point.y = lemipc->player.pos.y + 1;
	while (i != -1)
	{
		if (is_vec_point_in(lemipc, next_point))
			points[y] = get_board_value(lemipc->map,
				next_point.x, next_point.y);
		else
			points[y] = -1;
		next_point.x += 1;
		if (i % 3 == 0)
		{
			next_point.x -= 3;
			next_point.y -= 1;
		}
		i--;
		y++;
	}
}

int			check_values_around(t_lemipc *lemipc, int *points)
{
	int			i;
	int			y;

	i = 0;
	y = 0;
	while (i != 9)
	{
		if (points[i] != lemipc->player.team
			&& points[i] != 0 && points[i] != -1)
		{
			while (y != 9)
			{
				if (points[y] == points[i] && (y != i)
					&& points[y] != 0 && points[y] != -1)
					return (B_TRUE);
				y++;
			}
			y = 0;
		}
		i++;
	}
	return (B_FALSE);
}

/*
**	For the win check, Ill look for enemy targets.
**	If there are none, then we win.
*/

int			is_game_over(t_lemipc *lemipc)
{
	int		i;
	int		single_team_found;

	if (lemipc->player.is_dead == 1)
		return (B_TRUE);
	i = 0;
	single_team_found = 1;
	while (i < (BOARD_WIDTH * BOARD_HEIGHT))
	{
		if (lemipc->map[i] != 0
			&& lemipc->map[i] != (lemipc->player.team)
			&& lemipc->map[i] != -1)
		{
			single_team_found = 0;
			break ;
		}
		i++;
	}
	if (single_team_found == 1)
	{
		lemipc->winning_team = lemipc->player.team;
		return (B_TRUE);
	}
	return (B_FALSE);
}
