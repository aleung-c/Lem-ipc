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

// TODO: When player 1 1 dies, display is taken off....
// Also, on speed 0, the memory is not freed.

void		play_turn(t_lemipc *lemipc)
{
	// char			*msg;
	int				move_ret;
	// t_vec2			target;

	// steps:
	// ----- check if im dead.
	lock_semaphore(lemipc->sem_id, 1);
	if (am_i_dead(lemipc) == B_TRUE && lemipc->player.is_dead == B_FALSE)
	{
		// printf(KMAG "player team %d - #%d - DEAD%s\n",
		// 	lemipc->player.team, lemipc->player.nb, KRESET);
		lemipc->player.is_dead = B_TRUE;
		set_board_value(lemipc->map, lemipc->player.pos.x,
			lemipc->player.pos.y, 0);
		unlock_semaphore(lemipc->sem_id, 1);
	}
	unlock_semaphore(lemipc->sem_id, 1);
	if (lemipc->player.is_dead == B_FALSE)
	{
		// ----- Read on the MsgQ for orders/changes
		lemipc->player.cur_msg = check_communications(lemipc);
		if (lemipc->player.cur_msg)
		{
			// process msg;
			// printf("#%d received: %s\n",
			// 	lemipc->player.nb, lemipc->player.cur_msg);
			lemipc->player.target_pos = set_target_from_msg(lemipc,
											lemipc->player.cur_msg);
			if (lemipc->player.target_pos.x != -1)
			{
				lemipc->player.assisting = 1;
				// printf("assisting!\n");
				// free(lemipc->player.cur_msg);
				lemipc->player.cur_msg = NULL;
			}
		}

		// acting when turn comes.
		if (timespec_is_over(lemipc->turn_delay))
		{
			if (lemipc->player.assisting == 0)
			{
				// nothing going on, ill attack the closest.
				lemipc->player.target_pos = get_target(lemipc);
			}

			// moving toward the target.
			lock_semaphore(lemipc->sem_id, 1);
			move_ret = move_toward(&lemipc->player, lemipc->map, lemipc->player.target_pos);
			unlock_semaphore(lemipc->sem_id, 1);

			// if available and pinning down an enemy, ill call for help.
			if (lemipc->player.requesting_assistance == 0
				&& lemipc->player.assisting == 0
				&& get_distance(lemipc->player.pos,
					lemipc->player.target_pos) <= 1)
			{
				call_team(lemipc, lemipc->player.target_pos);
				lemipc->player.requesting_assistance = 1;
			}
			// if assisting and assist point reached.
			if (lemipc->player.assisting == 1
				&& get_distance(lemipc->player.pos, lemipc->player.target_pos) <= 2)
			{
				lemipc->player.assisting = 0;
				// printf("Assist reached!\n");
			}

			if (lemipc->player.requesting_assistance == 1
				&& get_board_value(lemipc->map, lemipc->player.target_pos.x,
					lemipc->player.target_pos.y) == 0)
			{
				// target moved or dead. reseting call.
				lemipc->player.requesting_assistance = 0;
			}

			// reset delay timer
			get_time(&lemipc->turn_delay);
			add_nsec_to_timespec(&lemipc->turn_delay,
				MS_TURN_DELAY * 1000000);
		}
	}
}
