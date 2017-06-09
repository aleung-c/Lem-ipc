/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_game_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 14:42:53 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/09 14:42:55 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

void	get_game_args(t_lemipc *lemipc, int argc, char **argv)
{
	if (argc == 3)
	{
		lemipc->nb_team = ft_atoi(argv[1]);
		if (lemipc->nb_team == 0)
		{
			ft_putendl(KRED "Error: Invalid team number" KRESET);
			exit(-1);
		}
		lemipc->nb_player_per_team = ft_atoi(argv[2]);
		if (lemipc->nb_player_per_team == 0)
		{
			ft_putendl(KRED "Error: Invalid number of player per team" KRESET);
			exit(-1);
		}
	}
}
