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
	lemipc->player.team = 0;
	lemipc->player.nb = 1;
	srand(time(NULL));
	init_cur_player(lemipc, 1, 1);
	lemipc->is_parent = 1;
	while (team_i < lemipc->nb_team)
	{
		while (player_i < lemipc->nb_player_per_team)
		{
			lemipc->pid = fork();
			if (lemipc->pid >= 0) // fork was successful
			{
				if (lemipc->pid == 0)
				{
					lemipc->is_parent = 0;
					srand(time(NULL) + team_i + player_i);
					// ft_putstr("Child process:\n");
					init_cur_player(lemipc, team_i + 1, player_i + 1);
					// sleep(5);

					// while (1)
					// {
					// 	sleep(2);
					// 	move_in_dir(&lemipc->player, lemipc->map, RIGHT);	
					// }
					// shmdt(lemipc->map);
					break;
				}
				else
				{
					// Parent process
					// ft_putstr("Parent process\n");
				}
			}
			else // fork failed
			{
				perror("Fork");
				exit(-1);
			}
			player_i++;
		}
		if (lemipc->pid == 0)
		{
			break ;
		}
		team_i++;
		player_i = 0;
	}
}

/*
**	Since we fork the starting process, it is NOT NEEDED to 
**	call shmget() and shmat() again.
*/

void	init_cur_player(t_lemipc *lemipc, int team, int nb)
{
	t_vec2		spawn_pos;

	spawn_pos.x = rand() % BOARD_WIDTH;
	spawn_pos.y = rand() % BOARD_HEIGHT;
	while (get_board_value(lemipc->map, spawn_pos.x, spawn_pos.y) != '0')
	{
		// if case already occupied, go on looking for an empty case;
		spawn_pos.x += 1;
		if (spawn_pos.x == BOARD_WIDTH)
		{
			spawn_pos.x = 0;
			spawn_pos.y += 1;
			if (spawn_pos.y == BOARD_HEIGHT)
			{
				spawn_pos.y = 0;
			}
		}
	}

	lemipc->player.team = team;
	lemipc->player.nb = nb;
	lemipc->player.pos.x = rand() % BOARD_WIDTH;
	lemipc->player.pos.y = rand() % BOARD_HEIGHT;

	
	// TODO: block sh segment with semaphore.
	set_board_value(lemipc->map, lemipc->player.pos.x, lemipc->player.pos.y, 48 + lemipc->player.nb);

	ft_putendl(KGRN "player joined:" KRESET);
	ft_putstr("team ");
	ft_putnbr(lemipc->player.team);
	ft_putstr("\nnumber ");
	ft_putnbr(lemipc->player.nb);
	ft_putchar('\n');
	printf("pos = %dx %dy\n", lemipc->player.pos.x, lemipc->player.pos.y);
	ft_putchar('\n');
}
