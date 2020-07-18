/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_point_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 13:09:44 by thboura           #+#    #+#             */
/*   Updated: 2020/07/02 18:14:17 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool					add_start(t_env *env, t_vec3f *position,
	t_sector *sector)
{
	if (check_if_already_exists(env, position)
		|| pickup_already_exists(env, position) != UINT64_MAX)
	{
		send_notify("Position already taken.", 0xFF0000, env);
		return (false);
	}
	env->current_map->level.start.position.x = position->x;
	env->current_map->level.start.position.z = position->z;
	env->current_map->level.start.position.y = sector->floor + LEVEL_HEIGHT;
	env->current_map->level.start.sector_id = sector->id;
	env->current_map->level.start.available = true;
	return (true);
}

bool					add_end(t_env *env, t_vec3f *position, t_sector *sector)
{
	if (check_if_already_exists(env, position)
		|| pickup_already_exists(env, position) != UINT64_MAX)
	{
		send_notify("Position already taken.", 0xFF0000, env);
		return (false);
	}
	env->current_map->level.end.position.x = position->x;
	env->current_map->level.end.position.z = position->z;
	env->current_map->level.end.position.y = sector->floor + LEVEL_HEIGHT;
	env->current_map->level.end.sector_id = sector->id;
	env->current_map->level.end.available = true;
	return (true);
}

static bool				check_inside(t_level_param *tmp_param,
	t_sector *tmp_sector)
{
	if (tmp_param->start.available
		&& tmp_param->start.sector_id == tmp_sector->id
		&& !inside(&(t_vec2f){tmp_param->start.position.x,
			tmp_param->start.position.z}, tmp_sector, false))
		return (false);
	if (tmp_param->end.available
		&& tmp_param->end.sector_id == tmp_sector->id
		&& !inside(&(t_vec2f){tmp_param->end.position.x,
			tmp_param->end.position.z}, tmp_sector, false))
		return (false);
	return (true);
}

bool					verify_sector_level_points(t_env *env, t_point *point)
{
	t_sector		*tmp_sector;
	size_t			i;

	i = 0;
	while (i < point->sector->total)
	{
		tmp_sector = *(t_sector **)map_get_index(point->sector, i);
		if (check_inside(&env->current_map->level, tmp_sector) == false)
			return (false);
		i++;
	}
	return (true);
}
