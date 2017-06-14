/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgq_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:43:13 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/13 12:43:16 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

void		init_msgq(t_lemipc *lemipc)
{
	int i;

	lemipc->msgq_ids = (int *)malloc(sizeof(int) * lemipc->nb_team);
	i = 0;
	while (i < lemipc->nb_team)
	{
		if ((lemipc->msgq_ids[i] = msgget(i + 1, IPC_CREAT | 0666)) == -1)
		{
			perror("init_msg: msgget: msgget failed");
			exit(1);
		}
		i++;
	}
	printf(KYEL "%d msg queue(s) initialized.\n" KRESET, i);
}


