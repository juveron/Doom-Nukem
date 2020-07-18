/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 18:04:17 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/06 18:04:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"
#include "clipping_internal.h"
#include "rasterizer.h"

static t_vec4f	get_normal(t_triangle_raster *tri)
{
	t_vec4f normal;
	t_vec4f	line1;
	t_vec4f	line2;

	line1 = vec4f_sub(tri->vertex[1].v, tri->vertex[0].v);
	line2 = vec4f_sub(tri->vertex[2].v, tri->vertex[0].v);
	normal = vec4f_cross(line1, line2);
	normal = vec4f_normalize(normal);
	return (normal);
}

static bool		check_clip_screen(t_triangle_raster *triangle)
{
	triangle->vertex[0].v.x = (triangle->vertex[0].v.x + 1) / 2
		* WIDTH_;
	triangle->vertex[0].v.y = (1 - (triangle->vertex[0].v.y + 1)
		* 0.5f) * HEIGHT_;
	triangle->vertex[1].v.x = (triangle->vertex[1].v.x + 1) / 2
		* WIDTH_;
	triangle->vertex[1].v.y = (1 - (triangle->vertex[1].v.y + 1)
		* 0.5f) * HEIGHT_;
	triangle->vertex[2].v.x = (triangle->vertex[2].v.x + 1) / 2
		* WIDTH_;
	triangle->vertex[2].v.y = (1 - (triangle->vertex[2].v.y + 1)
		* 0.5f) * HEIGHT_;
	clip_screen(triangle);
	return (true);
}

static void		clip_triangle_p2(t_triangle_raster *proj)
{
	t_vec4f				normal;

	proj->vertex[0].v_texture.x = proj->vertex[0].v_texture.x
		/ proj->vertex[0].v.w;
	proj->vertex[1].v_texture.x = proj->vertex[1].v_texture.x
		/ proj->vertex[1].v.w;
	proj->vertex[2].v_texture.x = proj->vertex[2].v_texture.x
		/ proj->vertex[2].v.w;
	proj->vertex[0].v_texture.y = proj->vertex[0].v_texture.y
		/ proj->vertex[0].v.w;
	proj->vertex[1].v_texture.y = proj->vertex[1].v_texture.y
		/ proj->vertex[1].v.w;
	proj->vertex[2].v_texture.y = proj->vertex[2].v_texture.y
		/ proj->vertex[2].v.w;
	proj->vertex[0].v_texture.z = 1.f / proj->vertex[0].v.w;
	proj->vertex[1].v_texture.z = 1.f / proj->vertex[1].v.w;
	proj->vertex[2].v_texture.z = 1.f / proj->vertex[2].v.w;
	proj->vertex[0].v = vec4f_div(proj->vertex[0].v, proj->vertex[0].v.w);
	proj->vertex[1].v = vec4f_div(proj->vertex[1].v, proj->vertex[1].v.w);
	proj->vertex[2].v = vec4f_div(proj->vertex[2].v, proj->vertex[2].v.w);
	normal = get_normal(proj);
	if (vec4f_dot(normal, (t_vec4f){0, 0, -1, 1}) <= 0.f)
		check_clip_screen(proj);
}

void			clip_triangle(t_triangle_raster *view, t_matrix4 *m_p)
{
	int					num_clip;
	t_triangle_raster	clipped[2];
	t_triangle_raster	proj;
	int					i;

	view->color = 0;
	num_clip = triangle_clip_plane(&(t_plane){(t_vec4f){0.f, 0.f, -0.1f, 1.f},
			(t_vec4f){0.f, 0.f, -1.f, 1.f}}, view, clipped);
	i = 0;
	while (i < num_clip)
	{
		proj = clipped[i];
		mul_matrix4_vec4f(&clipped[i].vertex[0].v, &proj.vertex[0].v, m_p);
		mul_matrix4_vec4f(&clipped[i].vertex[1].v, &proj.vertex[1].v, m_p);
		mul_matrix4_vec4f(&clipped[i].vertex[2].v, &proj.vertex[2].v, m_p);
		clip_triangle_p2(&proj);
		i++;
	}
}
