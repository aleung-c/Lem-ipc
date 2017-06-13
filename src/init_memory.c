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

void		init_shm_segment(t_lemipc *lemipc)
{
	lemipc->shm_id = shmget(SHM_MAP_KEY,
		sizeof(int) * (BOARD_WIDTH * BOARD_HEIGHT), IPC_CREAT | 0666);
	if (lemipc->shm_id < 0)
	{
		perror("init_board: shmget");
		exit(1);
	}
	// Attach the segment
	if ((lemipc->map = shmat(lemipc->shm_id, NULL, 0)) == (int *)-1)
	{
		perror("init_board: shmat");
		exit(1);
	}
}

void		init_semaphores(t_lemipc *lemipc)
{
	// Init semaphore
	lemipc->sem_id = semget(SEM_KEY, 1, SHM_R | SHM_W);
}
