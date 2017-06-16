/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 14:30:50 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/13 14:30:51 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

/*
**	Init the shared segment memory for the FIRST player.
**	That is why I use the flag IPC_EXCL to make it fail
**	if the segment exists already.
*/

void		init_shm_segment(t_lemipc *lemipc)
{
	lemipc->shm_id = shmget(SHM_MAP_KEY,
		sizeof(int) * (BOARD_WIDTH * BOARD_HEIGHT),
		IPC_CREAT | IPC_EXCL | 0666);
	if (lemipc->shm_id < 0)
	{
		perror("init_board: shmget");
		clean_all();
		exit(1);
	}
	if ((lemipc->map = shmat(lemipc->shm_id, NULL, 0)) == (int *)-1)
	{
		perror("init_board: shmat");
		clean_all();
		exit(1);
	}
}

void		init_semaphores(t_lemipc *lemipc)
{
	lemipc->sem_id = semget(IPC_PRIVATE, 1, SHM_R | SHM_W);
	if (lemipc->sem_id == -1)
	{
		perror("init_semaphores: semget");
		clean_all();
		exit (-1);
	}
}
