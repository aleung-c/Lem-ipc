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
	
	ft_putendl("Game datas:");
	ft_putnbr(lemipc.nb_team);
	ft_putendl(" teams");
	ft_putnbr(lemipc.nb_player_per_team);
	ft_putendl(" player per teams");

	init_board(&lemipc);

	lemipc.starter_pid = getpid();
	//srand(12);
	init_players(&lemipc);

	if (getpid() == lemipc.starter_pid)
	{
		init_display(&lemipc);

		while (1)
		{
			display_game_board(&lemipc);
			// sleep(1);
		}
		end_display(&lemipc);
	}
	ft_putstr("hello child\n");
}
