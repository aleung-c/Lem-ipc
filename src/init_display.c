/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 14:54:28 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/09 14:54:28 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

void	init_display(t_lemipc *lemipc)
{
	int			max_x;
	int			max_y;

	if ((lemipc->mainwin = initscr()) == NULL)
	{
		perror("ncurses");
		exit(-1);
	}
	getmaxyx(stdscr, max_x, max_y);
	if (max_x < BOARD_WIDTH || max_y < BOARD_HEIGHT)
	{
		endwin();
		ft_putstr(KRED "Shellscreen too small! Resize please!\n" KRESET);
		exit(-1);
	}
}


void		display_game_board(t_lemipc *lemipc)
{
	int		i;

	i = 0;
	while (i != (BOARD_HEIGHT * BOARD_WIDTH))
	{
		mvwaddch(lemipc->mainwin, i / BOARD_HEIGHT, i % BOARD_HEIGHT, lemipc->map[i]);
		i++;
	}
	refresh();
}

void		end_display(t_lemipc *lemipc)
{
    delwin(lemipc->mainwin);
    endwin();
    refresh();
}