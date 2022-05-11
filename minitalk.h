/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:35:29 by mcorso            #+#    #+#             */
/*   Updated: 2022/05/11 16:52:15 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>

static inline void	write_buffer(int len, char *buffer)
{
	write(1, buffer, len);
	write(1, "\n", 1);
}

static inline void	write_byte(int sig, unsigned char *buffer, int offset)
{
	if (sig == SIGUSR1)
		*buffer |= (1 << offset);
	else
		*buffer &= ~(1 << offset);
}

void	*ft_calloc(size_t count, size_t size)
{
	char			*dst;
	unsigned char	total;
	unsigned char	i;

	i = 0;
	total = count * size;
	dst = malloc(total);
	if (!dst)
		return (NULL);
	while (total--)
	{
		dst[i] = 0;
		i++;
	}
	return ((void *)dst);
}

static inline pid_t	to_pid(char *src)
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

static inline void	print_pid(pid_t pid)
{
	char	nb;

	if (pid <= 0)
		return ;
	print_pid(pid / 10);
	nb = (pid % 10) + '0';
	write(1, &nb, 1);
}

void	*ft_calloc(size_t count, size_t size);

#endif