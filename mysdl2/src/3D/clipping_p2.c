/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 12:05:39 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/02 12:05:39 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clipping_internal.h"

t_vec4f			intersect_plane(t_plane *plane, t_vec4f *line_start,
	t_vec4f *line_end, float *t)
{
	float	ad;

	ad = vec4f_dot(*line_start, plane->n);
	*t = (vec4f_dot(plane->n, plane->p) - ad) / (vec4f_dot(*line_end, plane->n)
		- ad);
	return (vec4f_add(*line_start, vec4f_mul(vec4f_sub(*line_end,
		*line_start), *t)));
}

static t_u32	one_vertex_insider_p2(t_clip *clip, t_plane *plane,
	t_triangle_raster *out, float t)
{
	out[0].vertex[2].v = intersect_plane(plane, &clip->inside_points[0]->v,
		&clip->outside_points[1]->v, &t);
	out[0].vertex[2].v_texture.x = t * (clip->outside_points[1]->v_texture.x
		- clip->inside_points[0]->v_texture.x)
		+ clip->inside_points[0]->v_texture.x;
	out[0].vertex[2].v_texture.y = t * (clip->outside_points[1]->v_texture.y
		- clip->inside_points[0]->v_texture.y)
		+ clip->inside_points[0]->v_texture.y;
	out[0].vertex[2].v_texture.z = t * (clip->outside_points[1]->v_texture.z
		- clip->inside_points[0]->v_texture.z)
		+ clip->inside_points[0]->v_texture.z;
	out[0].color = 0xFF0000;
	return (1);
}

t_u32			one_vertex_inside(t_clip *clip, t_plane *plane,
	t_triangle_raster out[2])
{
	float	t;

	out[0].vertex[0].v = clip->inside_points[0]->v;
	out[0].vertex[0].v_texture = clip->inside_points[0]->v_texture;
	out[0].vertex[1].v = intersect_plane(plane, &clip->inside_points[0]->v,
		&clip->outside_points[0]->v, &t);
	out[0].vertex[1].v_texture.x = t * (clip->outside_points[0]->v_texture.x
		- clip->inside_points[0]->v_texture.x)
		+ clip->inside_points[0]->v_texture.x;
	out[0].vertex[1].v_texture.y = t * (clip->outside_points[0]->v_texture.y
		- clip->inside_points[0]->v_texture.y)
		+ clip->inside_points[0]->v_texture.y;
	out[0].vertex[1].v_texture.z = t * (clip->outside_points[0]->v_texture.z
		- clip->inside_points[0]->v_texture.z)
		+ clip->inside_points[0]->v_texture.z;
	return (one_vertex_insider_p2(clip, plane, out, t));
}

static t_u32	two_vertices_inside_p2(t_clip *clip, t_triangle_raster out[2],
		float t)
{
	out[1].vertex[2].v_texture.x = t * (clip->outside_points[0]->v_texture.x
		- clip->inside_points[1]->v_texture.x)
		+ clip->inside_points[1]->v_texture.x;
	out[1].vertex[2].v_texture.y = t * (clip->outside_points[0]->v_texture.y
		- clip->inside_points[1]->v_texture.y)
		+ clip->inside_points[1]->v_texture.y;
	out[1].vertex[2].v_texture.z = t * (clip->outside_points[0]->v_texture.z
		- clip->inside_points[1]->v_texture.z)
		+ clip->inside_points[1]->v_texture.z;
	out[1].color = 0x0000FF;
	return (2);
}

t_u32			two_vertices_inside(t_clip *clip, t_plane *plane,
	t_triangle_raster out[2])
{
	float	t;

	out[0].vertex[0].v = clip->inside_points[0]->v;
	out[0].vertex[1].v = clip->inside_points[1]->v;
	out[0].vertex[0].v_texture = clip->inside_points[0]->v_texture;
	out[0].vertex[1].v_texture = clip->inside_points[1]->v_texture;
	out[0].vertex[2].v = intersect_plane(plane, &clip->inside_points[0]->v,
		&clip->outside_points[0]->v, &t);
	out[0].vertex[2].v_texture.x = t * (clip->outside_points[0]->v_texture.x
		- clip->inside_points[0]->v_texture.x)
		+ clip->inside_points[0]->v_texture.x;
	out[0].vertex[2].v_texture.y = t * (clip->outside_points[0]->v_texture.y
		- clip->inside_points[0]->v_texture.y)
		+ clip->inside_points[0]->v_texture.y;
	out[0].vertex[2].v_texture.z = t * (clip->outside_points[0]->v_texture.z
		- clip->inside_points[0]->v_texture.z)
		+ clip->inside_points[0]->v_texture.z;
	out[0].color = 0x00FF00;
	out[1].vertex[1].v = clip->inside_points[1]->v;
	out[1].vertex[1].v_texture = clip->inside_points[1]->v_texture;
	out[1].vertex[0].v = out[0].vertex[2].v;
	out[1].vertex[0].v_texture = out[0].vertex[2].v_texture;
	out[1].vertex[2].v = intersect_plane(plane, &clip->inside_points[1]->v,
		&clip->outside_points[0]->v, &t);
	return (two_vertices_inside_p2(clip, out, t));
}
