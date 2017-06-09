/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 16:03:48 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/08 16:03:50 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

int		main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putendl(KRED "Usage: ./lemipc [nb_team] [nb_player_per_team]" KRESET);
		exit(-1);
	}
	lemipc(argc, argv);
	return (0);
}
