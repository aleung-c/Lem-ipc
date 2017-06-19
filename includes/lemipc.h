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
# include <sys/sem.h>
# include <sys/msg.h>
# include <stdio.h> //
# include <errno.h>
# include <curses.h>
# include <time.h>
# include <math.h>
# include "../libft/libft.h"

# ifdef __MACH__
#  include <mach/clock.h>
#  include <mach/mach.h>
# endif

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
** --------------- CONTROL VALUES --------------- //
*/

# define BOARD_WIDTH 20
# define BOARD_HEIGHT 20
# define MS_TURN_DELAY 200

/*
** --------------- CONTROL VALUES --------------- //
*/

/*
** ----- Game defines
*/

# define SHM_MAP_KEY 4242
# define SHM_MAP_KEY2 4343
# define SEM_KEY 1234
# define SEM_KEY2 2345
# define MSG_SIZE 128

# define SEARCH_SAMPLES 6



/*
** ----- ncurse display defines
*/

# define EMPTY_CASE '.'

typedef enum				e_bool
{
	B_FALSE,
	B_TRUE
}							t_bool;

typedef enum				e_dir
{
							UP,
							RIGHT,
							DOWN,
							LEFT
}							t_dir;

/*
** ----- Program structs
*/

typedef struct				s_message
{
    long					type;
    char					text[MSG_SIZE];
}							t_message;

typedef struct				s_vec2
{
	int						x;
	int						y;
}							t_vec2;

typedef struct				s_player
{
	int						is_dead;

	int						team;
	int						nb;
	t_vec2					pos;

	t_vec2					target_pos;

	int						requesting_assistance;
	int						assisting;
	char					*cur_msg;
}							t_player;

typedef struct				s_lemipc
{
	int						nb_connected_players;
	int						is_parent;
	int						nb_team;
	int						*nb_player_per_team;

	int						shm_id;
	int						*map;

	int						init_shm_id;
	int						*game_started;

	int						sem_id;

	int						winning_team;
	int						*msgq_ids;

	t_player				player;

	struct timespec			turn_delay;

	WINDOW					*mainwin;

	pid_t					starter_pid;
	pid_t					pid;
}							t_lemipc;

/*
**	----- GLOBAL VAR -----
*/

t_lemipc					g_lemipc;

/*
**	----- GLOBAL VAR -----
*/

/*
**	----- Functions prototypes.
*/

void						sig_handler(int signo);

void						lemipc();
void						lemipc_init(int argc, char **argv);
void						lemipc_main_loop(t_lemipc *lemipc);
void						lemipc_on_end(t_lemipc *lemipc);

void						get_game_args(t_lemipc *lemipc, int argc,
								char **argv);
int							check_game_args(t_lemipc *lemipc);


void						init_game(t_lemipc *lemipc);
void						clear_map(int *map);

/*
**	init players -> fork() is used here.
*/

void						init_players(t_lemipc *lemipc);
void						init_cur_player(t_lemipc *lemipc, int team, int nb);
t_vec2						set_player_spawn_position(t_lemipc *lemipc);
void						init_player_variables(t_player *player, int team,
									int nb, t_vec2 spawn_pos);

/*
**	ncurse display functions.
*/

void						init_display(t_lemipc *lemipc);
void						display_game_board(t_lemipc *lemipc);
void						end_display(t_lemipc *lemipc);

/*
**	Game commands
*/

int							move_toward(t_player *player, int *map,
								t_vec2 target_pos);
int							move_in_dir(t_player *player, int *map, t_dir dir);
void						set_move_modifiers(int *x_move, int *y_move,
								t_dir dir);

int							am_i_dead(t_lemipc *lemipc);
void						get_values_around(t_lemipc *lemipc, int *points);
int							check_values_around(t_lemipc *lemipc, int *points);
int							is_game_over(t_lemipc *lemipc);

t_dir						find_dir(t_vec2 origine, int *map, t_vec2 target_pos);

/*
**	Gameplay
*/

void						play_turn(t_lemipc *lemipc);

/*
**	Team Management
*/

char						*check_communications(t_lemipc *lemipc);
void						call_team(t_lemipc *lemipc, t_vec2 target);
t_vec2						set_target_from_msg(t_lemipc *lemipc, char *msg);
void						send_msg_to_team(t_lemipc *lemipc, char *msg_text);

/*
**	Target management
*/

t_vec2						get_target(t_lemipc *lemipc);
t_vec2						distance_search(t_lemipc *lemipc);
int							stock_targets(t_lemipc *lemipc,
								t_vec2 *found_targets, int x, int y);
t_vec2						get_closest_target(t_lemipc *lemipc,
								t_vec2 *found_targets, int i);

/*
**	Board tools - board_tools.c
*/

int							get_board_value(int *board, int x, int y);
void						set_board_value(int *board, int x, int y,
								int val);
int							is_vec_point_in(t_lemipc *lemipc, t_vec2 point);
int							is_point_in(t_lemipc *lemipc, int x, int y);

/*
**	Tools
*/

int							get_distance(t_vec2 origine, t_vec2 destination);

void						get_time(struct timespec *ts);
struct timespec				timespec_diff(struct timespec *start,
								struct timespec *stop);
int							timespec_is_over(struct timespec time_end);
void						add_nsec_to_timespec(struct timespec *time,
								long nanosec);
void						add_delay_time(t_lemipc *lemipc);

/*
**	Semaphore handling.
*/

void						lock_semaphore(int sem_id, int sem);
void						unlock_semaphore(int sem_id, int sem);

/*
**	Msg queue
*/

void						init_msgq(t_lemipc *lemipc);

/*
**	Init memory
*/

void						init_shm_segment(t_lemipc *lemipc);
void						init_shm_segment_flag(t_lemipc *lemipc);
void						init_semaphores(t_lemipc *lemipc);

/*
**	Clean memory
*/

void						clean_all();
void						clean_shm_segment();
void						clean_semaphores();
void						clean_msgq();
void						kill_cur_process();

#endif
