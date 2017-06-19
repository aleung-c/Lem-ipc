/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:44:07 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/13 16:44:08 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

/*
**	Main function for the game play: this is an actual turn for the
**	current player. He will play when his delay time is up.
**	But, the checks are made at every loop turn -> more stable.
*/

void		play_turn(t_lemipc *lemipc)
{
	lock_semaphore(lemipc->sem_id, 1);
	if (am_i_dead(lemipc) == B_TRUE && lemipc->player.is_dead == B_FALSE)
	{
		lemipc->player.is_dead = B_TRUE;
		set_board_value(lemipc->map, lemipc->player.pos.x,
			lemipc->player.pos.y, 0);
		unlock_semaphore(lemipc->sem_id, 1);
	}
	unlock_semaphore(lemipc->sem_id, 1);
	if (lemipc->player.is_dead == B_FALSE)
	{
		check_for_team_comms(lemipc);
		if (timespec_is_over(lemipc->turn_delay))
		{
			if (lemipc->player.assisting == 0)
				lemipc->player.target_pos = get_target(lemipc);
			movement_action(lemipc);
			after_move_behavior(lemipc);
			add_delay_time(lemipc);
		}
	}
}

void		check_for_team_comms(t_lemipc *lemipc)
{
	lemipc->player.cur_msg = check_communications(lemipc);
	if (lemipc->player.cur_msg)
	{
		lemipc->player.target_pos = set_target_from_msg(lemipc,
			lemipc->player.cur_msg);
		if (lemipc->player.target_pos.x != -1)
		{
			lemipc->player.assisting = 1;
			lemipc->player.cur_msg = NULL;
		}
	}
}

/*
**	The moment where the cur player will actually move on the board.
*/

void		movement_action(t_lemipc *lemipc)
{
	lock_semaphore(lemipc->sem_id, 1);
	move_toward(&lemipc->player, lemipc->map, lemipc->player.target_pos);
	unlock_semaphore(lemipc->sem_id, 1);
}

/*
**	Where ill handle the decision AFTER the movement:
**
**	- if available and pinning down an enemy, ill call for help.
**
**	- if assisting and assist point reached, ill go back to normal mode.
**
**	- if target moved or dead-> reseting call.
*/

void		after_move_behavior(t_lemipc *lemipc)
{
	if (lemipc->player.requesting_assistance == 0
		&& lemipc->player.assisting == 0
		&& get_distance(lemipc->player.pos,
			lemipc->player.target_pos) <= 1)
	{
		call_team(lemipc, lemipc->player.target_pos);
		lemipc->player.requesting_assistance = 1;
	}
	if (lemipc->player.assisting == 1
		&& get_distance(lemipc->player.pos, lemipc->player.target_pos) <= 2)
	{
		lemipc->player.assisting = 0;
	}
	if (lemipc->player.requesting_assistance == 1
		&& get_board_value(lemipc->map, lemipc->player.target_pos.x,
			lemipc->player.target_pos.y) == 0)
	{
		lemipc->player.requesting_assistance = 0;
	}
}
