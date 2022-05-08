/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:35:29 by mcorso            #+#    #+#             */
/*   Updated: 2022/04/15 19:30:26 by mcorso           ###   ########.fr       */
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

void	handle(int sig);
void	print_pid(pid_t pid);
pid_t	to_pid(char *src);

#endif