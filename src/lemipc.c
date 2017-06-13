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

void	lemipc(int argc, char **argv)
{
	// t_lemipc			lemipc;

	ft_putstr("Hello lemipc\n");

	get_game_args(&g_lemipc, argc, argv);
	
	// TODO : protect against less cases than players.

	ft_putendl("Game datas:");
	ft_putnbr(g_lemipc.nb_team);
	ft_putendl(" teams");
	ft_putnbr(g_lemipc.nb_player_per_team);
	ft_putendl(" player per teams");

	g_lemipc.starter_pid = getpid();
	init_game(&g_lemipc);
	init_players(&g_lemipc);
	// forked from here.
	sleep(2);
	while (1)
	{
		// start process displays board.
		if (g_lemipc.is_parent == 1)
		{
			init_display(&g_lemipc);

			display_game_board(&g_lemipc);
			sleep(2);
		}
		// but every process decides their moves.
		if (g_lemipc.player.is_dead == 0)
		{
			// steps:
			// ----- check if im dead.

			// ----- check if target is set.
				// if not, set target and sync teammates.

			// ----- move toward target.

		}
	}
	end_display(&g_lemipc);
	sig_handler(SIGINT);
}
