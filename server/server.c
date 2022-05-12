/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:50:18 by mcorso            #+#    #+#             */
/*   Updated: 2022/05/12 15:20:21 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static void	reset_all(char **buffer, pid_t *last_pid, int *i, int *offset)
{
	free(*buffer);
	*buffer = NULL;
	*last_pid = 0;
	*offset = 6;
	*i = 0;
}

static void	manage_buffer(char **buffer, int len)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = *buffer;
	*buffer = ft_calloc(len + 1, sizeof(**buffer));
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
/* Debug
void	print_mem(char *buffer)
{
	int i;
	int bit = 0;
	int offset;

	i = 0;
	offset = 8;
	while (buffer[i])
	{
		while (offset--)
		{
			bit = buffer[i] & (1 << offset);
			if (bit)
				write(1, "1", 1);
			else
				write(1, "0", 1);
			write(1, " ", 1);
		}
		write(1, "\n", 1);
		offset = 8;
		i++;
	}
} */

static void	handle_sigusr(int sig, siginfo_t *meta, void *context)
{
	static int		i = 0;
	static int		offset = 6;
	static char		*buffer = NULL;
	static pid_t	last_pid = 0;

	(void)context;
	if (last_pid && meta->si_pid != last_pid)
		reset_all(&buffer, &last_pid, &i, &offset);
	last_pid = meta->si_pid;
	if (offset == 6)
		manage_buffer(&buffer, i);
	if (sig == SIGUSR1)
		buffer[i] |= (1 << offset);
	else
		buffer[i] &= ~(1 << offset);
	if (offset-- == 0)
	{
		if (buffer[i++] == '\0')
			write_buffer(i - 1, buffer);
		offset = 6;
	}
	usleep(100);
	kill(last_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sender;

	sender.sa_flags = SA_SIGINFO;
	sender.sa_sigaction = handle_sigusr;
	sigemptyset(&sender.sa_mask);
	sigaction(SIGUSR1, &sender, NULL);
	sigaction(SIGUSR2, &sender, NULL);
	print_pid(getpid());
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
}
