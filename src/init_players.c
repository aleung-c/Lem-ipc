/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:24:59 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/09 15:25:00 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

void	init_players(t_lemipc *lemipc)
{
	int			team_i;
	int			player_i;

	team_i = 0;
	player_i = 1;
	// set start player ids
	lemipc->player.team = 1;
	lemipc->player.nb = 1;
	init_cur_player(lemipc, 1, 1);
	while (team_i < lemipc->nb_team)
	{
		while (player_i < lemipc->nb_player_per_team)
		{
			lemipc->pid = fork();
			if (lemipc->pid >= 0) // fork was successful
			{
				if (lemipc->pid == 0) 
				{
					srand(player_i);
					ft_putstr("Child process:\n");
					init_cur_player(lemipc, team_i + 1, player_i + 1);
					sleep(5);
				}
				else
				{
					// Parent process
					ft_putstr("Parent process\n");
				}
			}
			else // fork failed
			{
				perror("Fork");
				exit(-1);
			}
			player_i++;
		}
		team_i++;
		player_i = 0;
	}
}

void	init_cur_player(t_lemipc *lemipc, int team, int nb)
{
	lemipc->player.team = team;
	lemipc->player.nb = nb;
	lemipc->player.pos.x = rand() % BOARD_WIDTH;
	lemipc->player.pos.y = rand() % BOARD_WIDTH;

	// TODO: not working for the parent starter process;
	if (getpid() != lemipc->starter_pid)
	{
		// in child, reattach map;
		lemipc->shm_id = shmget(SHM_MAP_KEY,
		sizeof(char) * (BOARD_WIDTH * BOARD_HEIGHT), IPC_CREAT | 0666);

		// Attach the segment
		if ((lemipc->map = shmat(lemipc->shm_id, NULL, 0)) == (char *) -1)
		{
			perror("shmat");
			exit(1);
		}
	}
	// TODO: block sh segment with semaphore.
	set_board_value(lemipc->map, lemipc->player.pos.x, lemipc->player.pos.y, 48 + lemipc->player.nb);

	ft_putendl(KGRN "player joined:" KRESET);
	ft_putstr("team ");
	ft_putnbr(lemipc->player.team);
	ft_putstr("\nnumber ");
	ft_putnbr(lemipc->player.nb);
	ft_putchar('\n');
	ft_putchar('\n');
}
