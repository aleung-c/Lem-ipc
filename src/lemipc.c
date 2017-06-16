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
	if (check_game_args(&g_lemipc) == -1)
		exit(-1);
	g_lemipc.starter_pid = getpid();
	init_game(&g_lemipc);
	init_players(&g_lemipc);
	usleep(30);
	if (g_lemipc.is_parent == 1)
	{
		init_display(&g_lemipc);
	}
	while (1)
	{
		if (g_lemipc.is_parent == 1)
		{
			display_game_board(&g_lemipc);
		}
		if (is_game_over(&g_lemipc) == B_TRUE)
			break ;
		if (g_lemipc.player.is_dead == 0)
			play_turn(&g_lemipc);
		else if (g_lemipc.player.is_dead == 1
			&& g_lemipc.is_parent == 0)
			break ;
	}
	if (g_lemipc.is_parent == 1)
		end_display(&g_lemipc);
	if (g_lemipc.winning_team != -1)
	{
		clear();
		printf("Team #%d won!\n", g_lemipc.winning_team);
	}
	clean_all();
}
