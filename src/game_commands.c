/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 15:28:32 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/12 15:28:34 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

void		move_in_dir(t_player *player, int *map, t_dir dir)
{
	int			y_move;
	int			x_move;
	t_vec2		new_pos;

	set_move_modifiers(&x_move, &y_move, dir);
	new_pos.x = player->pos.x + x_move;
	new_pos.y = player->pos.y + y_move;
	if ((new_pos.x >= 0 && new_pos.x < BOARD_WIDTH)
		&& (new_pos.y >= 0 && new_pos.y < BOARD_HEIGHT)
		&& get_board_value(map, new_pos.x, new_pos.y) == 0)
	{
		set_board_value(map, player->pos.x, player->pos.y, 0);
		set_board_value(map, new_pos.x, new_pos.y, player->team);
		player->pos.x = new_pos.x;
		player->pos.y = new_pos.y;
	}
	else
	{
		printf("player cant move there\n");
		return ;
	}
}

void		set_move_modifiers(int *x_move, int *y_move, t_dir dir)
{
	if (dir == UP)
	{
		*x_move = 0;
		*y_move = 1;
	}
	else if (dir == RIGHT)
	{
		*x_move = 1;
		*y_move = 0;
	}
	else if (dir == DOWN)
	{
		*x_move = 0;
		*y_move = -1;
	}
	else if (dir == LEFT)
	{
		*x_move = -1;
		*y_move = 0;
	}
}