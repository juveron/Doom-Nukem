/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision_p2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 16:54:53 by thboura           #+#    #+#             */
/*   Updated: 2020/06/12 13:17:41 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision_internal.h"

bool		check_collision_p8(t_env *env, t_collision_handler *handler)
{
	if (!handler->in)
	{
		env->player.transform->position = handler->new_pos;
		free(handler);
		return (false);
	}
	return (true);
}

void		collide(t_env *env, t_collision_handler *handler)
{
	handler->new_pos = vec3f_add(handler->new_pos,
		handler->col);
	handler->in = true;
	handler->capsule.start = handler->new_pos;
	handler->capsule.end = handler->new_pos;
	handler->capsule.end.y -= env->player.height
		- (handler->capsule.radius * 2);
}

static void	check_collision_p7(t_env *env, t_collision_handler *handler,
	size_t j, t_wall *wall)
{
	if (capsule_triangle_check(&handler->col, &handler->capsule,
		&wall[j].triangle[2]))
		collide(env, handler);
	if (capsule_triangle_check(&handler->col, &handler->capsule,
		&wall[j].triangle[3]))
		collide(env, handler);
}

static void	check_collision_p6(t_env *env, t_collision_handler *handler,
	size_t j, t_wall *wall)
{
	if (capsule_triangle_check(&handler->col, &handler->capsule,
		&wall[j].triangle[0]))
		collide(env, handler);
	if (capsule_triangle_check(&handler->col, &handler->capsule,
		&wall[j].triangle[1]))
		collide(env, handler);
}

void		check_collision_p5(t_env *env, t_collision_handler *handler)
{
	t_wall	*wall;
	size_t	j;

	wall = handler->sector->walls.items;
	j = 0;
	while (j < handler->sector->walls.total)
	{
		if (wall[j].wall_location & WALL_TOP || !wall[j].wall_location)
			check_collision_p6(env, handler, j, wall);
		if (wall[j].wall_location & WALL_BOTTOM)
			check_collision_p7(env, handler, j, wall);
		j++;
	}
}
