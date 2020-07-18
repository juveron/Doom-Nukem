/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:02:46 by killian           #+#    #+#             */
/*   Updated: 2020/03/09 13:49:37 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clock.h"
#include <sys/time.h>

t_u64	get_elapsed_microseconds(void)
{
	struct timeval	clock;

	gettimeofday(&clock, NULL);
	return (clock.tv_sec * 1000000 + (clock.tv_usec));
}

t_u64	clock_get_microseconds(t_clock *clock)
{
	t_u64			elapsed_microseconds;

	elapsed_microseconds = clock->elapsed_time;
	if (!clock->paused)
		elapsed_microseconds += get_elapsed_microseconds() - clock->ref_time;
	return (elapsed_microseconds);
}

t_u64	clock_get_milliseconds(t_clock *clock)
{
	return (clock_get_microseconds(clock) / 1000);
}

double	clock_get_seconds(t_clock *clock)
{
	return ((double)clock_get_microseconds(clock) / 1000000.);
}

void	clock_pause(t_clock *clock)
{
	if (!clock->paused)
	{
		clock->elapsed_time += get_elapsed_microseconds() - clock->ref_time;
		clock->paused = true;
	}
}
