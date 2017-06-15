/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 18:30:17 by aleung-c          #+#    #+#             */
/*   Updated: 2017/06/13 18:30:18 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemipc.h"

char		*check_communications(t_lemipc *lemipc)
{
	t_message		*msg;
	long			msg_type;
	int				result;
	
	msg_type = 0;
	msg = (t_message *)malloc(sizeof(t_message));
	result = msgrcv(lemipc->msgq_ids[lemipc->player.team],
		(void *) msg, sizeof(msg->text),
		msg_type, MSG_NOERROR | IPC_NOWAIT);
	if (result == -1)
		return (NULL);
	return (&msg->text[0]);
}

/*
**	concatenation of msg + target x + target y
*/

void		call_team(t_lemipc *lemipc, t_vec2 target)
{
	char	msg[MSG_SIZE];
	char	*x_value_text;
	char	*y_value_text;

	ft_strncpy(msg, "R ", 2);

	x_value_text = ft_itoa(target.x);
	ft_strncpy(msg + 2, x_value_text, ft_strlen(x_value_text));

	ft_strncpy(msg + 2 + ft_strlen(x_value_text), " ", 1);
	y_value_text = ft_itoa(target.y);
	ft_strncpy(msg + 3 + ft_strlen(x_value_text),
		y_value_text, ft_strlen(y_value_text));
	ft_strncpy(msg + 3 + ft_strlen(x_value_text) + ft_strlen(y_value_text),
		"\0", 1);
	send_msg_to_team(lemipc, msg);
}

void		send_msg_to_team(t_lemipc *lemipc, char *msg_text)
{
	t_message		msg;
	long			msg_type;

	msg_type = 1;

	if (ft_strlen(msg_text) > MSG_SIZE)
	{
		ft_putendl("Error: Message too long for queue");
		exit (-1);
	}
	ft_strncpy(msg.text, msg_text, MSG_SIZE);

	msgsnd(lemipc->msgq_ids[lemipc->player.team],
		&msg, MSG_SIZE, IPC_NOWAIT);
}
