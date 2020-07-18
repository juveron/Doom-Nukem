/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_height.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:18:48 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 16:21:03 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	check_pickup(t_sector *sector, t_env *env)
{
	size_t			i;
	size_t			j;
	t_pickup_object	**pickup_object;
	t_render_object	**render;

	i = 0;
	pickup_object = env->current_map->pickup_objects.items;
	render = env->objects_manager.remaining_object.items;
	while (i < env->current_map->pickup_objects.total)
	{
		if (pickup_object[i]->sector_id == sector->id)
		{
			j = 0;
			while (j < env->objects_manager.remaining_object.total)
			{
				if (vec3f_equal(&pickup_object[i]->pos,
						&render[j]->transform.position))
					render[j]->transform.position.y = sector->floor
							+ PICKUP_HEIGHT;
				++j;
			}
			pickup_object[i]->pos.y = sector->floor + PICKUP_HEIGHT;
		}
		++i;
	}
}

void		update_height(t_sector *sector, t_env *env)
{
	if (env->current_map->level.start.available
		&& env->current_map->level.start.sector_id == sector->id)
	{
		env->current_map->level.start.position.y = sector->floor
				+ PICKUP_HEIGHT;
		if (env->app_state == APP_EDITOR_GAME)
			env->levels_manager.start_obj->transform.position.
				y = env->current_map->level.start.position.y;
	}
	if (env->current_map->level.end.available
		&& env->current_map->level.end.sector_id == sector->id)
	{
		env->current_map->level.end.position.y = sector->floor + PICKUP_HEIGHT;
		if (env->app_state == APP_EDITOR_GAME)
			env->levels_manager.end_obj->transform.position.
				y = env->current_map->level.end.position.y;
	}
	check_pickup(sector, env);
}
