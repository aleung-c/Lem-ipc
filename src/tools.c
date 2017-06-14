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
/*
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
}*/