/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:28:34 by mcorso            #+#    #+#             */
/*   Updated: 2022/05/11 16:50:52 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static void	handle(int sig)
{
	(void)sig;
	return ;
}

static void	send_char(pid_t pid, char to_send)
{
	int	offset;

	offset = 8;
	while (offset--)
	{
		if (to_send & (1 << offset))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
	}
}

static void	client_handler(pid_t pid, char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		send_char(pid, msg[i++]);
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	signal(SIGUSR1, handle);
	if (argc == 3)
		client_handler(to_pid(argv[1]), argv[2]);
	else
		write(1, "./client [PID] [MSG]\n", 21);
	return (0);
}
