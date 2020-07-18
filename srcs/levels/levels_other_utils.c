/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_other_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:33:37 by thboura           #+#    #+#             */
/*   Updated: 2020/03/04 15:23:46 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		delete_level_point(t_env *env, t_level_point *point, bool record)
{
	bool	is_start;

	if (!point || !env->levels_manager.editor.active)
	{
		send_notify("No level point to delete.", 0xFF0000, env);
		return (true);
	}
	point->available = false;
	if (&env->current_map->level.start == point)
		is_start = true;
	else
		is_start = false;
	if (record)
		return (delete_level_point_event(env, point, is_start));
	return (true);
}

bool		verify_sector_in_levels(t_env *env, t_sector *sector)
{
	if (env->current_map->level.start.available
		&& env->current_map->level.start.sector_id == sector->id
		&& inside(&(t_vec2f){env->current_map->level.start.position.x,
		env->current_map->level.start.position.z}, sector, false))
		return (true);
	if (env->current_map->level.end.available
		&& env->current_map->level.end.sector_id == sector->id
		&& inside(&(t_vec2f){env->current_map->level.end.position.x,
		env->current_map->level.end.position.z}, sector, false))
		return (true);
	return (false);
}
