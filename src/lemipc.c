/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:14:07 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/08 17:14:11 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

/*
**	First function for lemipc main body.
*/

void	lemipc(int argc, char **argv)
{
	lemipc_init(argc, argv);
	lemipc_main_loop(&g_lemipc);
	lemipc_on_end(&g_lemipc);
}

/*
**	The Initialization part of the lemipc.
**	We init the memory, the players, and the display.
**	The fork() occurs here in init_players().
*/

void	lemipc_init(int argc, char **argv)
{
	get_game_args(&g_lemipc, argc, argv);
	if (check_game_args(&g_lemipc) == -1)
		exit(-1);
	g_lemipc.starter_pid = getpid();
	init_game(&g_lemipc);
	init_players(&g_lemipc);
	if (g_lemipc.is_parent == 1)
		init_display(&g_lemipc);
}

/*
**	The main loop for the program. Start when everything is
**	initialized and ready to roll.
*/

void	lemipc_main_loop(t_lemipc *lemipc)
{
	while (1)
	{
		if (lemipc->is_parent == 1)
			display_game_board(lemipc);
		if (*lemipc->game_status == GAME_STARTED)
		{
			if (lemipc->player.is_dead == 0)
				play_turn(lemipc);
			else
				break ;
			if (is_game_over(lemipc) == B_TRUE)
				break ;
			if (lemipc->winning_team != -1)
				break ;
		}
		if (*lemipc->game_status == GAME_END)
			break ;
	}
	if (lemipc->is_parent == 1)
	{
		while (*lemipc->game_status != GAME_END)
			display_game_board(lemipc);
	}
}

/*
**	The last part of the program.
**	Very important as the ipcs DO NOT clean
**	themselves in on the system.
*/

void	lemipc_on_end(t_lemipc *lemipc)
{
	if (lemipc->is_parent == 1)
	{
		end_display(lemipc);
	}
	if (g_lemipc.winning_team != -1)
	{
		clear();
		lock_semaphore(lemipc->sem_id, 1);
		*lemipc->game_status = GAME_END;
		ft_putstr(KYEL "Team #");
		ft_putnbr(lemipc->winning_team);
		ft_putendl(" won!" KRESET);
		unlock_semaphore(lemipc->sem_id, 1);
	}
	clean_all();
}
