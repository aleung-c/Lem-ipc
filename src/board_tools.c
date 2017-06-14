/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:14:56 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/09 12:14:57 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

int			get_board_value(int *board, int x, int y)
{
	return (board[(y * BOARD_WIDTH) + x]);
}

void		set_board_value(int *board, int x, int y, int val)
{
	board[(y * BOARD_WIDTH) + x] = val;
}

int			is_vec_point_in(t_lemipc *lemipc, t_vec2 point)
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

int			is_point_in(t_lemipc *lemipc, int x, int y)
{
	(void)lemipc;
	if (x >= BOARD_WIDTH || x < 0
		|| y >= BOARD_HEIGHT || y < 0)
	{
		return (B_FALSE);
	}
	else
	{
		return (B_TRUE);
	}
}