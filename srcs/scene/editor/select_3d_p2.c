/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_3d_p2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:50:06 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 14:23:32 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_3d_internal.h"

void		check_selection_ceil(t_selec_internal *s)
{
	t_triangle	*triangle;
	t_vec3f		normal;

	if (s->sector->has_roof)
	{
		triangle = s->sector->triangle_top.items;
		if (s->sector->triangle_top.total == 0)
			return ;
		normal = get_normal(&triangle[0]);
		if (vec3f_dot(normal, s->ray.dir) > 0.f)
			return ;
		if (check_triangle_vector(s, &s->sector->triangle_top))
		{
			s->env->editor.selection.type = SELEC_CEIL;
			s->env->editor.selection.data.sector = s->sector;
			return ;
		}
	}
	return ;
}

void		check_selection_floor(t_selec_internal *s)
{
	t_triangle	*triangle;
	t_vec3f		normal;

	triangle = s->sector->triangle_bottom.items;
	if (s->sector->triangle_bottom.total == 0)
		return ;
	normal = get_normal(&triangle[0]);
	if (vec3f_dot(normal, s->ray.dir) > 0.f)
		return ;
	if (check_triangle_vector(s, &s->sector->triangle_bottom))
	{
		s->env->editor.selection.type = SELEC_FLOOR;
		s->env->editor.selection.data.sector = s->sector;
		return ;
	}
	return ;
}

static void	set_wall_data(t_selec_internal *s, float dist,
	t_wall_location wall_location)
{
	t_env	*env;

	env = s->env;
	s->dist = dist;
	env->editor.selection.type = SELEC_WALL;
	env->editor.selection.data.wall.wall = s->wall;
	env->editor.selection.data.wall.sector = s->sector;
	env->editor.selection.data.wall.
		location = wall_location;
}

static void	select_wall(t_triangle *triangle, t_selec_internal *s,
	t_wall_location location)
{
	size_t	i;
	t_vec3f	normal;
	float	dist;
	t_vec3f	vec;

	normal = get_normal(&triangle[0]);
	if (vec3f_dot(normal, s->ray.dir) <= 0.f)
	{
		i = 0;
		while (i < 2)
		{
			if (ray_intersect_triangle(s, &triangle[i], &vec))
			{
				dist = vec3f_dist(s->ray.pos, vec);
				if (dist < s->dist)
					set_wall_data(s, dist, location);
			}
			i++;
		}
	}
}

void		check_wall(t_selec_internal *s)
{
	t_wall	*walls;
	size_t	i;

	walls = s->sector->walls.items;
	i = 0;
	while (i < s->sector->walls.total)
	{
		s->wall = &walls[i];
		if (walls[i].neighbor)
		{
			if (walls[i].wall_location & WALL_TOP)
				select_wall(&walls[i].triangle[0], s, WALL_TOP);
			if (walls[i].wall_location & WALL_BOTTOM)
				select_wall(&walls[i].triangle[2], s, WALL_BOTTOM);
		}
		else
			select_wall(&walls[i].triangle[0], s, WALL_FULL);
		++i;
	}
}
