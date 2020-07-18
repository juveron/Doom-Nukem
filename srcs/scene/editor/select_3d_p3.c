/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_3d_p3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:50:06 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 16:18:14 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_3d_internal.h"

t_vec3f		get_normal(t_triangle *tri)
{
	t_vec3f normal;
	t_vec3f	line1;
	t_vec3f	line2;

	line1 = vec3f_sub(tri->vertex[1].v, tri->vertex[0].v);
	line2 = vec3f_sub(tri->vertex[2].v, tri->vertex[0].v);
	normal = vec3f_cross(line1, line2);
	normal = vec3f_normalize(normal);
	return (normal);
}

bool		ray_intersect_triangle(t_selec_internal *selec,
	t_triangle *triangle, t_vec3f *out)
{
	t_ray_intersect	s;

	s.edge1 = vec3f_sub(triangle->vertex[1].v, triangle->vertex[0].v);
	s.edge2 = vec3f_sub(triangle->vertex[2].v, triangle->vertex[0].v);
	s.h = vec3f_cross(selec->ray.dir, s.edge2);
	s.a = vec3f_dot(s.edge1, s.h);
	if (s.a > -0.0000001f && s.a < 0.0000001f)
		return (false);
	s.f = 1.f / s.a;
	s.s = vec3f_sub(selec->ray.pos, triangle->vertex[0].v);
	s.u = s.f * vec3f_dot(s.s, s.h);
	if (s.u < 0.f || s.u > 1.f)
		return (false);
	s.q = vec3f_cross(s.s, s.edge1);
	s.v = s.f * vec3f_dot(selec->ray.dir, s.q);
	if (s.v < 0.f || s.u + s.v > 1.f)
		return (false);
	s.t = s.f * vec3f_dot(s.edge2, s.q);
	if (s.t > 0.0000001f)
	{
		*out = vec3f_add(selec->ray.pos, vec3f_mul(selec->ray.dir, s.t));
		return (true);
	}
	else
		return (false);
}

bool		check_triangle_vector(t_selec_internal *s, t_vector *triangle)
{
	size_t		i;
	t_triangle	*triangles;
	t_vec3f		vec;
	float		dist;

	triangles = triangle->items;
	i = 0;
	while (i < triangle->total)
	{
		if (ray_intersect_triangle(s, &triangles[i], &vec))
		{
			dist = vec3f_dist(s->ray.pos, vec);
			if (dist < s->dist)
			{
				s->dist = dist;
				return (true);
			}
			return (false);
		}
		++i;
	}
	return (false);
}

static bool	init_right_menu_p2(t_env *env)
{
	set_visible(&env->gui.window->component, true);
	if (env->editor.selection.data.wall.location == WALL_TOP)
	{
		if (!init_wall_menu(env->editor.selection.data.wall.wall, true, env))
			return (false);
	}
	else if (env->editor.selection.data.wall.location == WALL_BOTTOM)
	{
		if (!init_wall_menu(env->editor.selection.data.wall.wall, false, env))
			return (false);
	}
	else
	{
		if (!init_wall_menu(env->editor.selection.data.wall.wall, true, env))
			return (false);
	}
	return (true);
}

bool		init_right_menu(t_env *env)
{
	if (env->editor.selection.type == SELEC_FLOOR)
	{
		set_visible(&env->gui.window->component, true);
		if (!init_sector_menu(&env->gui.sector_menu,
			env->editor.selection.data.sector, true, env))
			return (false);
	}
	else if (env->editor.selection.type == SELEC_CEIL)
	{
		set_visible(&env->gui.window->component, true);
		if (!init_sector_menu(&env->gui.sector_menu,
			env->editor.selection.data.sector, false, env))
			return (false);
	}
	else if (env->editor.selection.type == SELEC_WALL)
		return (init_right_menu_p2(env));
	return (true);
}
