/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 18:58:46 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/12 18:58:48 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

void						lock_semaphore(int sem_id, int sem)
{
	struct sembuf	sb;

	sb.sem_num = sem;
	sb.sem_op = -1;
	sb.sem_flg = SEM_UNDO;
	semop(sem_id, &sb, 1);
}

void						unlock_semaphore(int sem_id, int sem)
{
	struct sembuf	sb;

	sb.sem_num = sem;
	sb.sem_op = 1;
	sb.sem_flg = SEM_UNDO;
	semop(sem_id, &sb, 1);
}
