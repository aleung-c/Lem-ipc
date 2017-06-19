/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_management_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 19:12:14 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/19 19:12:15 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

void		parse_target_msg(char *msg, t_vec2 *ret)
{
	int		i;
	int		msg_len;

	i = 0;
	msg_len = ft_strlen(msg);
	while (i != msg_len)
	{
		if (msg[i] == ' ' && msg[i + 1])
		{
			if (ret->x == -1)
				ret->x = ft_atoi(&msg[i + 1]);
			else
				ret->y = ft_atoi(&msg[i + 1]);
		}
		i++;
	}
}
