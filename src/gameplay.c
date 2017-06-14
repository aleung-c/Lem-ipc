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

void		play_turn(t_lemipc *lemipc)
{
	char			*msg;
	t_vec2			target;

	// steps:
	// ----- check if im dead.
	if (am_i_dead(lemipc) == B_TRUE && lemipc->player.is_dead == false)
	{
		printf(KMAG "player team %d - #%d - DEAD%s\n", lemipc->player.team, lemipc->player.nb, KRESET);
		lemipc->player.is_dead = true;
		lock_semaphore(lemipc->sem_id, 1);
		set_board_value(lemipc->map, lemipc->player.pos.x, lemipc->player.pos.y, 0);
		unlock_semaphore(lemipc->sem_id, 1);
		if (getpid() != lemipc->starter_pid)
			kill_cur_process();
	}

	// ----- Read on the MsgQ for orders/changes
	msg = check_communications(lemipc);
	if (msg)
	{
		// process msg;
		// printf("Received: %s\n", msg);

		// exit(-1);
		// target = received target.
	}
	else
	{
		// ----- Select a target position
		target = get_target(lemipc);
		lock_semaphore(lemipc->sem_id, 1);
		move_toward(&lemipc->player, lemipc->map, target);
		unlock_semaphore(lemipc->sem_id, 1);
		if (get_distance(lemipc->player.pos, target) <= 2)
		{
			call_team(lemipc);
		}
	}

	// ----- move toward target.
	// lock_semaphore(lemipc->sem_id, 1);
	// move_in_dir(&lemipc->player, lemipc->map, rand() % 4);
	// unlock_semaphore(lemipc->sem_id, 1);
	// sleep(1);

	usleep(500000);
}
