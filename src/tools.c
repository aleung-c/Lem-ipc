/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 16:32:51 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/14 16:32:52 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

/*
**	returns the distance between 2 points, as in a manhattan-distance way.
*/

int		get_distance(t_vec2 origine, t_vec2 destination)
{
	return (abs(destination.x - origine.x) + abs(destination.y - origine.y));
}

/*
**	struct timeval
**	{
**		long	tv_sec;		// secondes
**		long	tv_usec;	// microsecondes -> 1 000 000 us == 1s
**	};
**	struct timespec
**	{
**		long	tv_sec;		// secondes
**		long	tv_nsec;	// nanosecondes -> 1 000 000 000 ns == 1s
**	};
*/

#ifdef __MACH__

void			get_time(struct timespec *ts)
{
	clock_serv_t	cclock;
	mach_timespec_t	mts;

	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
}

#else

void			get_time(struct timespec *ts)
{
	clock_gettime(CLOCK_REALTIME, ts);
}

#endif

struct timespec	timespec_diff(struct timespec *start, struct timespec *stop)
{
	struct timespec result;

	if ((stop->tv_nsec - start->tv_nsec) < 0)
	{
		result.tv_sec = stop->tv_sec - start->tv_sec - 1;
		result.tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
	}
	else
	{
		result.tv_sec = stop->tv_sec - start->tv_sec;
		result.tv_nsec = stop->tv_nsec - start->tv_nsec;
	}
	return (result);
}

int				timespec_is_over(struct timespec time_end)
{
	struct timespec	now;

	get_time(&now);
	if (now.tv_sec > time_end.tv_sec ||
		(now.tv_sec == time_end.tv_sec && now.tv_nsec >= time_end.tv_nsec))
		return (1);
	return (0);
}

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