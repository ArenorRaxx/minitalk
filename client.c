/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:28:34 by mcorso            #+#    #+#             */
/*   Updated: 2022/02/06 00:37:55 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static pid_t	to_pid(char *src)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = 0;
	while (src[i])
	{
		pid *= 10;
		pid += src[i] - '0';
		i++;
	}
	return (pid);
}

static void	send_char(pid_t pid, char to_send)
{
	int	offset;

	offset = 0;
	while (offset <= 7)
	{
		if (to_send & (1 << offset))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		offset++;
		usleep(500);
	}
}

static void	client_handler(pid_t pid, char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		send_char(pid, msg[i]);
		i++;
	}
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		client_handler(to_pid(argv[1]), argv[2]);
	else
		write(1, "./client [PID] [MSG]\n", 21);
	return (0);
}