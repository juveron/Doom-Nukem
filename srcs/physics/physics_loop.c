/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:39:28 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/11 15:07:30 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "mysdl2.h"

void	ph_add_update_func(t_ph_context *ph_context,
	bool (*update)(void *, float), void *param)
{
	ph_context->update = update;
	ph_context->param = param;
}

void	init_ph_context(t_ph_context *ph_context)
{
	ph_context->t = 0.0;
	ph_context->dt = DELTATIME;
	clock_restart(&ph_context->physics_clock);
	ph_context->current_time = clock_get_seconds(
		&ph_context->physics_clock);
	ph_context->accumulator = 0.0;
}

bool	ph_loop(t_ph_context *ph_context)
{
	double new_time;

	new_time = clock_get_seconds(&ph_context->physics_clock);
	ph_context->frame_time = new_time
		- ph_context->current_time;
	ph_context->current_time = new_time;
	ph_context->accumulator += ph_context->frame_time;
	while (ph_context->accumulator >= ph_context->dt)
	{
		if (!ph_context->update(ph_context->param, ph_context->dt))
			return (false);
		ph_context->accumulator -= ph_context->dt;
		ph_context->t += ph_context->dt;
	}
	return (true);
}
