/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 19:14:27 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/19 19:15:07 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

/*
**	Add nano seconds to the timespec. Dont forget to multiply your sec time by
**	1000000000, or by 1000000 if it is milliseconds.
**	Example:
**		add_nsec_to_timespec(&player->next_dinner_time,
**		FOOD_LIFE_TIME * serv->world_hdl.t_unit * 1000000000);
*/

void			add_nsec_to_timespec(struct timespec *time, long nanosec)
{
	time->tv_nsec += nanosec;
	while (time->tv_nsec > 1000000000)
	{
		time->tv_nsec -= 1000000000;
		time->tv_sec += 1;
	}
}

void			add_delay_time(t_lemipc *lemipc)
{
	static int	delay_val;

	delay_val = MS_TURN_DELAY;
	get_time(&lemipc->turn_delay);
	add_nsec_to_timespec(&lemipc->turn_delay,
		delay_val * 1000000);
}
