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
	int			i;

	team_i = 0;
	player_i = 1;
	i = 0;
	srand(time(NULL) ^ (getpid() << 16));
	init_cur_player(lemipc, 1, 1);
	get_time(&lemipc->turn_delay);
	add_nsec_to_timespec(&lemipc->turn_delay, 
		MS_TURN_DELAY * 1000000);
	lemipc->is_parent = 1;
	while (team_i < lemipc->nb_team)
	{
		while (player_i < lemipc->nb_player_per_team[team_i])
		{
			lemipc->pid = fork();
			if (lemipc->pid >= 0)
			{
				if (lemipc->pid == 0)
				{
					unlock_semaphore(g_lemipc.init_sem_id, 1);
					lemipc->is_parent = 0;
					srand(time(NULL) ^ (getpid() << 16));
					get_time(&lemipc->turn_delay);
					add_nsec_to_timespec(&lemipc->turn_delay, 
						MS_TURN_DELAY * 1000000);
					init_cur_player(lemipc, team_i + 1, player_i + 1);
					i++;
					break ;
				}
			}
			else
			{
				perror("Fork");
				clean_all();
				exit(-1);
			}
			player_i++;
		}
		if (lemipc->pid == 0 && getpid() != lemipc->starter_pid)
			break ;
		team_i++;
		player_i = 0;
	}
}

/*
**	Since we fork the starting process, it is NOT NEEDED to 
**	call shmget() and shmat() again.
**	The forked child inherit parents segments.
*/

void	init_cur_player(t_lemipc *lemipc, int team, int nb)
{
	t_vec2		spawn_pos;

	spawn_pos = set_player_spawn_position(lemipc);
	init_player_variables(&lemipc->player, team, nb, spawn_pos);
	lock_semaphore(lemipc->sem_id, 1);
	set_board_value(lemipc->map, lemipc->player.pos.x,
						lemipc->player.pos.y, lemipc->player.team);
	unlock_semaphore(lemipc->sem_id, 1);

	if (team == lemipc->nb_team && nb == lemipc->nb_player_per_team[lemipc->nb_team - 1])
	{
		*lemipc->game_started = 1;
	}

	// debug print.
	// ft_putendl(KGRN "player joined:" KRESET);
	// ft_putstr("team ");
	// ft_putnbr(lemipc->player.team);
	// ft_putstr("\nnumber ");
	// ft_putnbr(lemipc->player.nb);
	// ft_putchar('\n');
	// printf("pos = %dx %dy\n", lemipc->player.pos.x, lemipc->player.pos.y);
	// ft_putchar('\n');
}

t_vec2		set_player_spawn_position(t_lemipc *lemipc)
{
	t_vec2		spawn_pos;

	spawn_pos.x = rand() % BOARD_WIDTH;
	spawn_pos.y = rand() % BOARD_HEIGHT;
	while (get_board_value(lemipc->map, spawn_pos.x, spawn_pos.y) != 0)
	{
		spawn_pos.x += 2;
		if (spawn_pos.x >= BOARD_WIDTH)
		{
			spawn_pos.x = 0;
			spawn_pos.y += 1;
			if (spawn_pos.y >= BOARD_HEIGHT)
			{
				spawn_pos.y = 0;
			}
		}
	}
	return (spawn_pos);
}

void		init_player_variables(t_player *player, int team,
									int nb, t_vec2 spawn_pos)
{
	g_lemipc.winning_team = -1;
	player->is_dead = 0;
	player->team = team;
	player->nb = nb;
	player->pos.x = spawn_pos.x;
	player->pos.y = spawn_pos.y;
	player->requesting_assistance = 0;
	player->assisting = 0;
	player->cur_msg = NULL;
}
