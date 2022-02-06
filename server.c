/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:50:18 by mcorso            #+#    #+#             */
/*   Updated: 2022/02/06 00:49:43by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_sigusr(int sig)
{
	static int	offset;
	static char	buffer;

	if (sig == SIGUSR1)
		buffer |= (1 << offset);
	else
		buffer &= ~(1 << offset);
	offset++;
	if (offset == 8)
	{
		offset = 0;
		if (buffer == '\0')
		{
			write(1, &buffer, 1);
			write(1, "\n", 1);
		}
	}
}

static void	print_pid(pid_t pid)
{
	char	nb;

	if (pid <= 0)
		return ;
	print_pid(pid / 10);
	nb = (pid % 10) + '0';
	write(1, &nb, 1);	
}

int	main(void)
{
	print_pid(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, handle_sigusr);
	signal(SIGUSR2, handle_sigusr);
	while (1)
	{
		pause();
	}
}