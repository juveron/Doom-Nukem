/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:50:06 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 16:16:48 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_3d_internal.h"

static t_vec3f	screen_space_to_world(t_vec2f vec, t_camera *camera)
{
	t_matrix4	inv;
	t_vec4f		ndc_space;
	t_vec4f		out;
	t_vec3f		ret;

	inv = camera->m_invert;
	inv.m[3][0] = 0;
	inv.m[3][1] = 0;
	inv.m[3][2] = 0;
	inv = matrix_multiply(&inv, &camera->m_proj);
	inv = matrix_invert(&inv);
	ndc_space.x = 2.f * (vec.x / (float)WIDTH) - 1.f;
	ndc_space.y = 1.f - (2.f * (vec.y / (float)HEIGHT));
	ndc_space.z = 1;
	ndc_space.w = 1;
	mul_matrix4_vec4f(&ndc_space, &out, &inv);
	out = vec4f_div(out, out.w);
	ret = *(t_vec3f *)&out;
	ret = vec3f_normalize(ret);
	return (ret);
}

static bool		check_selection(t_selec_internal *s)
{
	size_t		i;
	t_sector	*sector;
	size_t		nb_sector;
	t_map		*sectors;

	i = 0;
	sectors = s->env->current_map->sectors;
	nb_sector = s->env->current_map->sectors->total;
	while (i < nb_sector)
	{
		sector = *(t_sector **)map_get_index(sectors, i);
		s->sector = sector;
		check_selection_ceil(s);
		check_selection_floor(s);
		check_wall(s);
		++i;
	}
	return (s->env->editor.selection.type != SELEC_NONE);
}

bool			selec(t_env *env)
{
	t_vec2i				mouse_pos;
	t_selec_internal	s;

	env->editor.selection.type = SELEC_NONE;
	mouse_pos = get_mouse_position();
	s.ray.dir = screen_space_to_world(vec2f(mouse_pos.x, mouse_pos.y),
		&env->camera);
	s.dist = INFINITY;
	s.ray.pos = env->camera.transform.position;
	s.env = env;
	if (check_selection(&s))
	{
		if (!init_right_menu(env))
			return (false);
	}
	return (true);
}
