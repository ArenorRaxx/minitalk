/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:35:29 by mcorso            #+#    #+#             */
/*   Updated: 2022/04/12 14:57:52 by mcorso           ###   ########.fr       */
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

#endif