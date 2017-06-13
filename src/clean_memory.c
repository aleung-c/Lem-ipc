/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 14:26:05 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/13 14:26:06 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

void	clean_shm_segment()
{
	// int		shm_id;
	// char	*map;

	// shm_id = shmget(SHM_MAP_KEY,
	// 	sizeof(char) * (BOARD_WIDTH * BOARD_HEIGHT), 0666);

	// if (shm_id < 0)
	// {
	// 	perror("sig_handler: shmget");
	// 	exit(1);
	// }
	// // Attach the segment
	// if ((map = shmat(shm_id, NULL, 0)) == (char *) -1)
	// {
	// 	perror("sig_handler: shmat");
	// 	exit(1);
	// }
	shmdt(g_lemipc.map);
	shmctl(g_lemipc.shm_id, IPC_RMID, NULL);
}

void	clean_semaphores()
{
	// int		sem_id;

	// sem_id = semget(SEM_KEY, 1, SHM_R | SHM_W);
	semctl(g_lemipc.sem_id, 1, IPC_RMID, NULL);
}

void	clean_msgq()
{
	int		i;
	int		msgq_id;

	i = 0;
	while (i < g_lemipc.nb_team)
	{
		if ((msgq_id = msgget(i + 1, 0666)) != -1)
		{
			msgctl(msgq_id, IPC_RMID, NULL);
		}
		i++;
	}
}

// TODO: make shmctl() calls to determine if im the last to clean the ressources.

void	kill_cur_process()
{
	shmdt(g_lemipc.map);
	exit(0);
}