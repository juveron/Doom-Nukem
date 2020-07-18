/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:13:19 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 14:34:15 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision_internal.h"

static void	init_collision_handler(t_collision_handler *handler, t_env *env,
	float dt)
{
	matrix_rotation(env->camera.transform.rotation.x,
		env->camera.transform.rotation.y, env->camera.transform.rotation.z,
		&handler->m_rot);
	mul_matrix4_vec3f(&(t_vec3f){0, 0, -1}, &handler->look_dir,
		&handler->m_rot);
	handler->look_dir = vec3f_mul(handler->look_dir, 2);
	handler->old_pos = env->player.transform->position;
	handler->new_pos = vec3f_add(vec3f_add(env->player.transform->position,
		env->player.new_pos), vec3f_mul(env->player.physic.velocity, dt));
	handler->capsule.start = handler->new_pos;
	handler->capsule.end = handler->new_pos;
	handler->capsule.radius = 0.5f;
	handler->capsule.end.y -= env->player.height - (handler->capsule.radius
		* 2);
}

static void	check_collision_p4(t_env *env, t_collision_handler *handler,
	size_t j)
{
	if (handler->sector->has_roof)
	{
		if (capsule_triangle_check(&handler->col, &handler->capsule,
			&handler->triangle2[j]))
		{
			env->player.physic.velocity.y = 0;
			collide(env, handler);
		}
	}
}

static bool	check_collision_p3(t_env *env, t_collision_handler *handler,
	size_t j)
{
	if (capsule_triangle_check(&handler->col, &handler->capsule,
		&handler->triangle[j]))
	{
		env->player.state |= 1 << ST_ON_GROUND;
		if (env->app_state == APP_GAME && handler->sector->floor_damage)
		{
			if (update_damage(env))
			{
				free(handler);
				return (0);
			}
		}
		env->player.physic.velocity.y = 0;
		collide(env, handler);
	}
	return (1);
}

bool		check_collision_p2(t_env *env, t_collision_handler *handler,
	size_t i)
{
	size_t	j;

	if (env->app_state == APP_EDITOR_GAME)
		handler->sector = *(t_sector **)map_get_index(env->current_map->
			sectors, i);
	else
		handler->sector = *(t_sector **)vector_get(&env->game->visible_sector,
			i);
	handler->triangle = handler->sector->triangle_bottom.items;
	handler->triangle2 = handler->sector->triangle_top.items;
	j = 0;
	while (j < handler->sector->triangle_bottom.total)
	{
		if (!check_collision_p3(env, handler, j))
			return (0);
		check_collision_p4(env, handler, j);
		j++;
	}
	return (1);
}

bool		check_collision(t_env *env, float dt)
{
	int					nb_pass;
	t_collision_handler	*handler;

	if (!(handler = (t_collision_handler *)ft_memalloc(
			sizeof(t_collision_handler))))
		return (0);
	init_collision_handler(handler, env, dt);
	nb_pass = -1;
	while (++nb_pass < 4)
	{
		if (check_collision_p9(handler, env))
			return (1);
	}
	env->player.transform->position = handler->new_pos;
	free(handler);
	return (1);
}
