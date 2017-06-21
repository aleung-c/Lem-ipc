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
		lemipc->nb_player_per_team =
		(int *)malloc(sizeof(int) * lemipc->nb_team);
		i = 0;
		while (i < lemipc->nb_team)
		{
			lemipc->nb_player_per_team[i] = ft_atoi(argv[i + 1]);
			if (lemipc->nb_player_per_team[i] < 1)
			{
				ft_putendl(KRED "Error: not enough member for team!" KRESET);
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

int		check_game_args(t_lemipc *lemipc)
{
	int		i;
	int		player_count;
	int		found_team_of_two;

	i = 0;
	player_count = 0;
	found_team_of_two = 0;
	while (i < lemipc->nb_team)
	{
		player_count += lemipc->nb_player_per_team[i];
		if (lemipc->nb_player_per_team[i] >= 2)
			found_team_of_two = 1;
		i++;
	}
	if (player_count >= (BOARD_WIDTH * BOARD_HEIGHT))
	{
		ft_putendl(KRED "Error: More player than map area" KRESET);
		return (-1);
	}
	if (found_team_of_two == 0)
	{
		ft_putendl(KRED "Error: One team should have two players" KRESET);
		return (-1);
	}
	return (check_game_args_2(lemipc));
}

int		check_game_args_2(t_lemipc *lemipc)
{
	(void)lemipc;
	if (BOARD_HEIGHT <= 0 || BOARD_WIDTH <= 0)
	{
		ft_putendl(KRED "Error: Invalid board size" KRESET);
		return (-1);
	}
	if (MS_TURN_DELAY < 0)
	{
		ft_putendl(KRED "Error: Invalid delay time value" KRESET);
		return (-1);
	}
	return (0);
}
