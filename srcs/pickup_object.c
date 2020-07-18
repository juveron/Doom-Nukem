/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickup_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:56:09 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/02 18:10:01 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

size_t	pickup_already_exists(t_env *env, t_vec3f *position)
{
	size_t			i;
	t_pickup_object	**pickup_objects;

	pickup_objects = env->current_map->pickup_objects.items;
	i = 0;
	while (i < env->current_map->pickup_objects.total)
	{
		if (pickup_objects[i]->pos.x == position->x
				&& pickup_objects[i]->pos.z == position->z)
			return (i);
		i++;
	}
	return (UINT64_MAX);
}

/*
**	return value:
**
**	0 = no_error
**	1 = fail but not critical error
**	2 = critical error, program need to be closed
*/

int		add_pickup_object_p2(t_env *env, t_vec3f *position,
	t_sector *sector, bool record)
{
	t_pickup_object	*pickup_object;

	if (!(pickup_object = ft_memalloc(sizeof(*pickup_object))))
		return (2);
	pickup_object->sector_id = sector->id;
	pickup_object->pos = (t_vec3f){position->x, sector->floor + PICKUP_HEIGHT,
		position->z};
	if (!vector_push(&env->current_map->pickup_objects, &pickup_object))
	{
		free(pickup_object);
		return (2);
	}
	if (record)
		if (!add_pickup_object_event(env, pickup_object))
			return (2);
	return (0);
}

int		add_pickup_object(t_env *env, t_vec3f *position, bool record)
{
	t_sector		*sector;

	if (!(sector = is_in_sector(env, &(t_vec2f){env->editor.position_map.v.x,
		env->editor.position_map.v.z}, false)))
	{
		send_notify("Pickup object must be inside a sector.", 0xFF0000, env);
		return (1);
	}
	if (pickup_already_exists(env, position) != UINT64_MAX
		|| check_if_already_exists(env, position))
	{
		send_notify("Position already taken.", 0xFF0000, env);
		return (1);
	}
	return (add_pickup_object_p2(env, position, sector, record));
}

/*
**	return value:
**
**	0 = no_error
**	1 = fail but not critical error
**	2 = critical error, program need to be closed
*/

int		delete_pickup_object(t_env *env, t_vec3f *pos, bool record)
{
	size_t			index;
	t_pickup_object	*pickup_object;
	size_t			sector_id;
	t_vec3f			tmp_pos;

	index = pickup_already_exists(env, pos);
	if (index == UINT64_MAX)
		return (1);
	pickup_object = *(t_pickup_object **)vector_get(&env->current_map->
		pickup_objects, index);
	sector_id = pickup_object->sector_id;
	tmp_pos = pickup_object->pos;
	free(pickup_object);
	if (!vector_delete(&env->current_map->pickup_objects, index))
		return (2);
	if (record)
		if (!delete_pickup_object_event(env, &tmp_pos, sector_id, index))
			return (2);
	return (0);
}

void	draw_pickup_object_editor(t_env *env)
{
	size_t			i;
	t_pickup_object	**pickup_objects;

	pickup_objects = env->current_map->pickup_objects.items;
	i = 0;
	while (i < env->current_map->pickup_objects.total)
	{
		draw_elipse(rect(pickup_objects[i]->pos.x * env->editor.zoom
			+ env->editor.offset_z.x, pickup_objects[i]->pos.z
			* env->editor.zoom + env->editor.offset_z.y,
			3, 3), 0xFF00FF, env->main_window->surface);
		i++;
	}
}
