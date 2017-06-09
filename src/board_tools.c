/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:14:56 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/09 12:14:57 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

char	get_board_value(char *board, int x, int y)
{
	return (board[(y * BOARD_WIDTH) + x]);
}

void	set_board_value(char *board, int x, int y, char val)
{
	board[(y * BOARD_WIDTH) + x] = val;
}
