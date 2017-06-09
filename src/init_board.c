/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:00:59 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/09 12:01:00 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

/*
**	Init the board and clears it with zeros.
*/

void	init_board(t_lemipc *lemipc)
{
	// Creates the segment.
	lemipc->shm_id = shmget(SHM_MAP_KEY,
		sizeof(char) * (BOARD_WIDTH * BOARD_HEIGHT), IPC_CREAT | 0666);
	if (lemipc->shm_id < 0)
	{
		perror("shmget");
		exit(1);
	}

	// Attach the segment
	if ((lemipc->map = shmat(lemipc->shm_id, NULL, 0)) == (char *) -1)
	{
		perror("shmat");
		exit(1);
	}
	clear_board(lemipc->map);
}

/*
**	Clears the board with zeros.
*/

void			clear_board(char *board)
{
	int i;
	int end;

	i = 0;
	end = BOARD_HEIGHT * BOARD_WIDTH;
	while (i != end)
	{
		board[i] = '0';
		i++;
	}
}
