/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:00:06 by killian           #+#    #+#             */
/*   Updated: 2020/03/09 13:49:53 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOCK_H
# define CLOCK_H

# include "libft.h"

typedef struct	s_clock
{
	t_u64			elapsed_time;
	t_u64			ref_time;
	bool			paused;
}				t_clock;

t_u64			get_elapsed_microseconds(void);
t_u64			clock_get_microseconds(t_clock *clock);
t_u64			clock_get_milliseconds(t_clock *clock);
double			clock_get_seconds(t_clock *clock);
void			clock_pause(t_clock *clock);
void			clock_unpause(t_clock *clock);
bool			clock_is_pause(t_clock *clock);
t_u64			clock_restart(t_clock *clock);
void			clock_set_milliseconds(t_clock *clock, t_u64 time);

#endif
