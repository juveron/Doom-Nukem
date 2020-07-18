/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 12:20:38 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 12:39:05 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	init_object_manager(t_env *env)
{
	SDL_Surface	*surface;

	if (!(env->objects_manager.material = mtl_create()))
		return (false);
	if (!(env->objects_manager.on_pickedup_object = create_event_handler(
		CUSTOM_EVENT_TYPE)))
		return (false);
	if (!(surface = import_tga("./assets/fragment2.tga", false)))
	{
		mtl_destroy(&env->objects_manager.material);
		return (false);
	}
	if (!(env->objects_manager.texture = create_texture("Pickup texture",
		surface, 0)))
	{
		mtl_destroy(&env->objects_manager.material);
		return (false);
	}
	if (!mtl_add_diffuse_texture(env->objects_manager.material,
		env->objects_manager.texture))
		return (false);
	return (true);
}

void	destroy_object_manager(t_env *env)
{
	destroy_texture(&env->objects_manager.texture);
	destroy_event_handler(env->objects_manager.on_pickedup_object);
	mtl_destroy(&env->objects_manager.material);
}

void	update_pickup_object(t_env *env)
{
	t_render_object	**remaining_objects;
	size_t			i;
	float			dist;

	remaining_objects = env->objects_manager.remaining_object.items;
	i = 0;
	while (i < env->objects_manager.remaining_object.total)
	{
		dist = vec3f_dist(env->camera.transform.position,
			remaining_objects[i]->transform.position);
		if (dist <= 1)
		{
			trigger_gui_custom_event(env->objects_manager.on_pickedup_object,
				remaining_objects[i]);
			destroy_render_object(&remaining_objects[i]);
			vector_delete(&env->objects_manager.remaining_object, i);
			remaining_objects = env->objects_manager.remaining_object.items;
		}
		i++;
	}
}

bool	draw_pickup_object(t_env *env, float dt)
{
	t_render_object	**render_objects;
	size_t			i;

	(void)dt;
	render_objects = env->objects_manager.remaining_object.items;
	i = 0;
	while (i < env->objects_manager.remaining_object.total)
	{
		update_transform(&render_objects[i]->transform);
		if (!draw_render_object(render_objects[i]))
			return (false);
		i++;
	}
	return (true);
}
