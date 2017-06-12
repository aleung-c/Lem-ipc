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

/*
**	Main drawing function. Used in the ever running loop.
*/

void		display_game_board(t_lemipc *lemipc)
{
	static int			max_x;
	static int			max_y;
	int					x;
	int					y;
	int					end_y;

	x = 0;
	y = 0;
	end_y = BOARD_HEIGHT - 1;
	getmaxyx(stdscr, max_x, max_y);
	if (max_x < BOARD_WIDTH || max_y < BOARD_HEIGHT)
	{
		endwin();
		ft_putstr(KRED "Shellscreen too small! Resize please!\n" KRESET);
		exit(-1);
	}
	clear();

	while (y != BOARD_HEIGHT)
	{
		while (x != BOARD_WIDTH)
		{
			mvwaddch(lemipc->mainwin, y, x, lemipc->map[(end_y * BOARD_WIDTH) + x]);
			x++;
		}
		y++;
		end_y--;
		x = 0;
	}

	// while (i != -1)
	// {
	// 	mvwaddch(lemipc->mainwin, i / BOARD_WIDTH, i % BOARD_WIDTH, lemipc->map[i]);
	// 	refresh();
	// 	i--;
	// }
	refresh();
}

void		end_display(t_lemipc *lemipc)
{
    delwin(lemipc->mainwin);
    endwin();
    refresh();
}