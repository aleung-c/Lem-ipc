/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:17:54 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/08 17:17:56 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEMIPC_H
# define LEMIPC_H

# include <sys/ipc.h>
# include <sys/shm.h>
# include <stdio.h>
# include <errno.h>
# include <curses.h>
# include "../libft/libft.h"

/*
**	color in text;
*/

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
# define KRESET "\x1B[0m"

/*
**	Semaphore lib union define
*/

# if !defined(__GNU_LIBRARY__) || defined(_SEM_SEMUN_UNDEFINED)
union semun
{
	int val; // value for SETVAL
	struct semid_ds* buf; // buffer for IPC_STAT, IPC_SET
	unsigned short* array; // array for GETALL, SETALL
	struct seminfo* __buf; // buffer for IPC_INFO
};
# endif

/*
** ----- Game defines
*/

# define BOARD_WIDTH 20
# define BOARD_HEIGHT 20
# define SHM_MAP_KEY 4242

/*
** ----- Program structs
*/

typedef struct				s_vec2
{
	int						x;
	int						y;
}							t_vec2;

typedef struct				s_player
{
	int						team;
	int						nb;
	t_vec2					pos;
}							t_player;

typedef struct				s_lemipc
{
	int						nb_team;
	int						nb_player_per_team;

	int						shm_id;
	char					*map;

	t_player				player;

	WINDOW					*mainwin;

	pid_t					starter_pid;
	pid_t					pid;
}							t_lemipc;



/*
**	----- Functions prototypes.
*/


void						lemipc();

void						get_game_args(t_lemipc *lemipc, int argc,
								char **argv);

void						init_board(t_lemipc *lemipc);
void						clear_board(char *board);

void						init_players(t_lemipc *lemipc);
void						init_cur_player(t_lemipc *lemipc, int team, int nb);

/*
**	ncurse display functions.
*/

void						init_display(t_lemipc *lemipc);
void						display_game_board(t_lemipc *lemipc);
void						end_display(t_lemipc *lemipc);

/*
**	Board tools - board_tools.c
*/

char						get_board_value(char *board, int x, int y);
void						set_board_value(char *board, int x, int y, char val);

#endif
