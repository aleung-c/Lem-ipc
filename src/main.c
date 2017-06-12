/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 16:03:48 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/08 16:03:50 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

int		main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putendl(KRED "Usage: ./lemipc [nb_team] [nb_player_per_team]" KRESET);
		exit(-1);
	}
	signal(SIGINT, sig_handler);
	lemipc(argc, argv);
	return (0);
}

void	sig_handler(int signo)
{
	int		shm_id;
	char	*map;


	if (signo == SIGINT)
	{
		printf("received SIGINT\n");
		shm_id = shmget(SHM_MAP_KEY,
			sizeof(char) * (BOARD_WIDTH * BOARD_HEIGHT), 0666);

		if (shm_id < 0)
		{
			perror("sig_handler: shmget");
			exit(1);
		}

		// Attach the segment
		if ((map = shmat(shm_id, NULL, 0)) == (char *) -1)
		{
			perror("sig_handler: shmat");
			exit(1);
		}
		shmdt(map);
		shmctl(shm_id, IPC_RMID, NULL);
	}
}
