/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:35:29 by mcorso            #+#    #+#             */
/*   Updated: 2022/04/14 22:40:20 by mcorso           ###   ########.fr       */
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

void	handle(int sig);
void	print_pid(pid_t pid);
void	manage_buffer(char **buffer, int len);
pid_t	to_pid(char *src);

#endif