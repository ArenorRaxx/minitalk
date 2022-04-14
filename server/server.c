/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:50:18 by mcorso            #+#    #+#             */
/*   Updated: 2022/04/14 22:37:09 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static void	reset_all(char **buffer, pid_t *last_pid, int *i, int *offset)
{
	free(*buffer);
	*buffer = NULL;
	*last_pid = 0;
	*offset = 0;
	*i = 0;
}

void	print_pid(pid_t pid)
{
	char	nb;

	if (pid <= 0)
		return ;
	print_pid(pid / 10);
	nb = (pid % 10) + '0';
	write(1, &nb, 1);
}

void	manage_buffer(char **buffer, int len)
{
	int		i;
	char	*tmp;

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
	static int		i = 0;
	static int		offset = 0;
	static char		*buffer = NULL;
	static pid_t	last_pid = 0;

	(void)context;
	if (last_pid && meta->si_pid != last_pid)
		reset_all(&buffer, &last_pid, &i, &offset);
	last_pid = meta->si_pid;
	manage_buffer(&buffer, i + 1);
	if (sig == SIGUSR1)
		buffer[i] |= (1 << offset);
	else
		buffer[i] &= ~(1 << offset);
	usleep(150);
	kill(last_pid, SIGUSR1);
	if (++offset == 8)
	{
		if (buffer[i++] == '\0')
		{
			write_buffer(i, buffer);
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
