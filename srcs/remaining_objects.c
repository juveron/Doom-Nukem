/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remaining_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 20:45:23 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 03:28:49 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	init_pickup_object(t_env *env, t_render_object **render_object,
	t_pickup_object **pickup_object, size_t i)
{
	ft_snprintf(env->buff, sizeof(env->buff), "Pickup object %lu", i);
	if (!(render_object[i] = create_render_object(env->buff,
		env->global_mesh.fragment_mesh, true,
		env->objects_manager.material)))
		return (false);
	render_object[i]->transform.position = pickup_object[i]->pos;
	render_object[i]->transform.scale = vec3f(0.3f, 0.3f, 0.3f);
	return (true);
}

bool		init_remaining_object(t_env *env)
{
	size_t			i;
	t_render_object	**render_object;
	t_pickup_object	**pickup_object;

	if (!vector_init_n(&env->objects_manager.remaining_object,
		sizeof(t_render_object *), env->current_map->pickup_objects.total))
		return (false);
	ft_bzero(env->objects_manager.remaining_object.items,
		sizeof(t_render_object *) * env->current_map->pickup_objects.total);
	pickup_object = env->current_map->pickup_objects.items;
	render_object = env->objects_manager.remaining_object.items;
	i = 0;
	while (i < env->objects_manager.remaining_object.total)
		if (!init_pickup_object(env, render_object, pickup_object, i++))
			return (false);
	return (true);
}

void		free_remaining_objects(t_env *env)
{
	size_t			i;
	t_render_object	**remianing_object;

	remianing_object = env->objects_manager.remaining_object.items;
	i = 0;
	while (i < env->objects_manager.remaining_object.total)
	{
		destroy_render_object(&remianing_object[i]);
		i++;
	}
	vector_free(&env->objects_manager.remaining_object);
	ft_printf("Free remaining objects\n");
}
