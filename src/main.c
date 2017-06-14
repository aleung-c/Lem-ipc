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
	if (argc < 3)
	{
		ft_putendl(KRED "Usage: ./lemipc [nb_player_for_team] ..." KRESET);
		exit(-1);
	}
	signal(SIGINT, sig_handler);
	lemipc(argc, argv);
	return (0);
}

void	sig_handler(int signo)
{
	if (signo == SIGINT || signo == SIGSTOP || signo == SIGKILL)
	{
		clean_all();
		end_display(&g_lemipc);
	}
}
