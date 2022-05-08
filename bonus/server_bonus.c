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

#include "../minitalk.h"

static void	reset_all(unsigned char **buf, pid_t *last_pid, int *i, int *offset)
{
	free(*buf);
	*buf = NULL;
	*last_pid = 0;
	*offset = 0;
	*i = 0;
}

static void	manage_buffer(unsigned char **buffer, int len)
{
	int				i;
	unsigned char	*tmp;

	i = 0;
	tmp = *buffer;
	*buffer = malloc(sizeof(**buffer) * len);
	if (!buffer)
	{
		write(1, "Malloc error.\n", 14);
		free(tmp);
		exit(EXIT_FAILURE);
	}
	if (!tmp)
		return ;
	while (i < len)
	{
		buffer[0][i] = tmp[i];
		i++;
	}
	free(tmp);
}

static void	handle_sigusr(int sig, siginfo_t *meta, void *context)
{
	static int				i = 0;
	static int				offset = 0;
	static pid_t			last_pid = 0;
	static unsigned char	*buffer = NULL;

	(void)context;
	if (last_pid && meta->si_pid != last_pid)
		reset_all(&buffer, &last_pid, &i, &offset);
	last_pid = meta->si_pid;
	manage_buffer(&buffer, i + 1);
	write_byte(sig, &buffer[i], offset);
	usleep(150);
	kill(last_pid, SIGUSR2);
	if (++offset == 9)
	{
		if (buffer[i++] == '\0')
		{
			write(1, buffer, i);
			write(1, "\n", 1);
			kill(meta->si_pid, SIGUSR1);
			reset_all(&buffer, &last_pid, &i, &offset);
		}
		offset = 0;
	}
}

int	main(void)
{
	struct sigaction	sender;

	sender.sa_flags = SA_SIGINFO;
	sender.sa_sigaction = handle_sigusr;
	print_pid(getpid());
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sender, NULL);
	sigaction(SIGUSR2, &sender, NULL);
	while (1)
	{
		pause();
	}
}