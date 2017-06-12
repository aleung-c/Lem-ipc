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
	t_lemipc			lemipc;
	

	ft_putstr("Hello lemipc\n");

	get_game_args(&lemipc, argc, argv);
	
	// TODO : protect against less cases than players.

	ft_putendl("Game datas:");
	ft_putnbr(lemipc.nb_team);
	ft_putendl(" teams");
	ft_putnbr(lemipc.nb_player_per_team);
	ft_putendl(" player per teams");

	init_board(&lemipc);

	lemipc.starter_pid = getpid();
	//srand(12);
	init_players(&lemipc);
	// forked from here.
	sleep(3);
	if (lemipc.is_parent == 1)
	{
		init_display(&lemipc);

		while (1)
		{
			display_game_board(&lemipc);
			// sleep(3);
			sleep(2);
		}
		end_display(&lemipc);
	}
	sig_handler(SIGINT);
	// ft_putstr("hello child\n");
}
