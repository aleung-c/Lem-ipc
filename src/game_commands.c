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

int			move_toward(t_player *player, int *map, t_vec2 target_pos)
{
	t_dir dir;

	dir = find_dir(player->pos, map, target_pos);
	return (move_in_dir(player, map, dir));
}

/*
**	To find the direction for the target, I made a beginning of 
**	A star search algorithm. I only check the distance to the 
**	the target for a single depth from the current position.
**	And when in doubt, I throw some random values.
*/

t_dir		find_dir(t_vec2 origine, int *map, t_vec2 target_pos)
{
	int			base_distance;
	t_vec2		simulated_point;

	base_distance = get_distance(origine, target_pos);
	simulated_point = origine;
	simulated_point.x -= 1;
	if (is_vec_point_in(NULL, simulated_point)
	&& get_board_value(map, simulated_point.x, simulated_point.y) == 0
	&& get_distance(simulated_point, target_pos) <= base_distance)
		return (LEFT);
	simulated_point = origine;
	simulated_point.x += 1;
	if (is_vec_point_in(NULL, simulated_point)
	&& get_board_value(map, simulated_point.x, simulated_point.y) == 0
	&& get_distance(simulated_point, target_pos) <= base_distance)
		return (RIGHT);
	simulated_point = origine;
	simulated_point.y -= 1;
	if (is_vec_point_in(NULL, simulated_point)
	&& get_board_value(map, simulated_point.x, simulated_point.y) == 0
	&& get_distance(simulated_point, target_pos) <= base_distance)
		return (DOWN);
	simulated_point = origine;
	simulated_point.y += 1;
	if (is_vec_point_in(NULL, simulated_point)
	&& get_board_value(map, simulated_point.x, simulated_point.y) == 0
	&& get_distance(simulated_point, target_pos) <= base_distance)
		return (UP);
	return (rand() % 4);
}

int			move_in_dir(t_player *player, int *map, t_dir dir)
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
		return (1);
	}
	else
	{
		return (0);
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
