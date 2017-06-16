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
	get_game_args(&g_lemipc, argc, argv);
	// TODO : protect against less cases than players.
	g_lemipc.starter_pid = getpid();
	init_game(&g_lemipc);
	init_players(&g_lemipc);
	// forked from here.
	sleep(1);
	while (1)
	{
		// start process displays board.
		if (g_lemipc.is_parent == 1)
		{
			init_display(&g_lemipc);
			display_game_board(&g_lemipc);
		}
		// but every process decides their moves.
		if (is_game_over(&g_lemipc) == B_TRUE)
			break ;
		if (g_lemipc.player.is_dead == 0)
		{
			play_turn(&g_lemipc);
		}
		else if (g_lemipc.is_parent == 0)
			break ;
	}
	if (g_lemipc.is_parent == 1)
		end_display(&g_lemipc);
	clean_all();
}
