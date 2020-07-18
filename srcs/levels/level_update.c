/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 07:45:31 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/15 03:37:11 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		set_current_map_by_index(t_env *env, t_u64 index)
{
	env->current_map_index = index;
	env->current_map = *(t_doom_map **)vector_get(&env->maps,
		env->current_map_index);
	if (env->current_map->level.start.available)
	{
		env->camera.transform.position = env->current_map->level.start.position;
		if (!set_source_position(env->sound_manager.audio_objects.
			start_of_level.source, env->current_map->level.start.position))
			return (false);
	}
	if (env->current_map->level.end.available)
	{
		if (!set_source_position(env->sound_manager.audio_objects.
			end_of_level.source, env->current_map->level.end.position))
			return (false);
	}
	env->hud.objs_in_map.remaining = UINT64_MAX;
	load_level_position(env);
	free_remaining_objects(env);
	init_remaining_object(env);
	if (index != 0)
		env->game->current_segment_time = clock_get_milliseconds(&env->hud.
			time);
	return (true);
}

static bool	verif_dist(t_env *env, float dist)
{
	if (dist <= 1.f)
	{
		if (env->objects_manager.remaining_object.total)
			;
		else if (env->current_map_index + 1 == env->maps.total)
		{
			init_win_state(env);
			init_win_menu(env);
		}
		else
			return (set_current_map_by_index(env, env->current_map_index + 1));
	}
	return (true);
}

bool		update_level(t_env *env, float dt)
{
	float	dist;

	if (!env->current_map->level.start.available
		|| !env->current_map->level.end.available)
		return (true);
	dist = vec3f_dist_sq(env->camera.transform.position,
		env->current_map->level.end.position);
	env->levels_manager.start_obj->transform.rotation.y += dt * 90
		* env->time_scale;
	env->levels_manager.end_obj->transform.rotation.y += dt * 90
		* env->time_scale;
	if (env->app_state == APP_GAME)
		return (verif_dist(env, dist));
	else
		return (true);
}

bool		draw_level(t_env *env)
{
	update_transform(&env->levels_manager.start_obj->transform);
	update_transform(&env->levels_manager.end_obj->transform);
	if (env->current_map->level.start.available)
		if (!draw_render_object(env->levels_manager.start_obj))
			return (false);
	if (env->current_map->level.end.available)
		if (!draw_render_object(env->levels_manager.end_obj))
			return (false);
	return (true);
}
