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
	int i;

	i = 0;
	if (argc >= 3)
	{
		lemipc->nb_team = argc - 1;
		lemipc->nb_player_per_team = (int *)malloc(sizeof(int) * lemipc->nb_team);
		i = 0;
		while (i < lemipc->nb_team)
		{
			lemipc->nb_player_per_team[i] = ft_atoi(argv[i + 1]);
			if (lemipc->nb_player_per_team[i] < 1)
			{
				ft_putendl(KRED "Error: Need at least one member for team!" KRESET);
				exit(-1);
			}
			i++;
		}
	}
	else
	{
		ft_putendl(KRED "Error: Need at least two teams!" KRESET);
		exit(-1);
	}
}
