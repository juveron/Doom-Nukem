/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 02:15:41 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 02:15:42 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	update_rotation_start(t_env *env)
{
	t_level_point	*point;

	if (get_key(SDL_SCANCODE_Q) || get_key(SDL_SCANCODE_E))
	{
		point = get_level_point(&env->
				current_map->level, &env->editor.position_map.v);
		if (point == &env->current_map->level.start)
		{
			if (get_key(SDL_SCANCODE_E))
				env->current_map->level.start.rotation += 120.f
						* env->ph_context.frame_time;
			if (get_key(SDL_SCANCODE_Q))
				env->current_map->level.start.rotation -= 120.f
						* env->ph_context.frame_time;
			env->need_redraw = true;
		}
	}
}
