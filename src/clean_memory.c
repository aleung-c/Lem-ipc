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

void	clean_all()
{
	lock_semaphore(g_lemipc.sem_id, 1);
	shmdt(g_lemipc.map);
	unlock_semaphore(g_lemipc.sem_id, 1);
	clean_semaphores();
	clean_msgq();
	clean_shm_segment();
}

void	clean_shm_segment()
{
	struct shmid_ds		buf;

	shmctl(g_lemipc.shm_id, IPC_STAT, &buf);
	if (buf.shm_nattch == 0)
	{
		shmctl(g_lemipc.shm_id, IPC_RMID, NULL);
		shmctl(g_lemipc.init_shm_id, IPC_RMID, NULL);
		printf(KGRN "- Shared memory cleaned!\n" KRESET);
	}

}

void	clean_semaphores()
{
	struct shmid_ds		buf;

	shmctl(g_lemipc.shm_id, IPC_STAT, &buf);
	if (buf.shm_nattch == 0)
	{
		semctl(g_lemipc.sem_id, 1, IPC_RMID, NULL);
		printf(KGRN "- Semaphore memory cleaned!\n" KRESET);
	}
}

void	clean_msgq()
{
	int					i;
	int					msgq_id;
	struct shmid_ds		buf;

	shmctl(g_lemipc.shm_id, IPC_STAT, &buf);
	if (buf.shm_nattch == 0)
	{
		i = 0;
		while (i < g_lemipc.nb_team)
		{
			if ((msgq_id = msgget(i + 1, 0666)) != -1)
				msgctl(msgq_id, IPC_RMID, NULL);
			i++;
		}
		printf(KGRN "- Message queue memory cleaned!\n" KRESET);
	}
}
