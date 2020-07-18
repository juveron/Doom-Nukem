/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:51:53 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/07 16:46:47 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clipping_internal.h"

static float	get_shortest_distance(t_vec4f *p, t_plane *plane)
{
	return (vec4f_dot(plane->n, *p)
		- vec4f_dot(plane->n, plane->p));
}

void			check_points(t_clip *clip, t_plane *plane,
		t_triangle_raster *in)
{
	if (get_shortest_distance(&in->vertex[0].v, plane) >= 0)
		clip->inside_points[clip->count_inside_point++] = &in->vertex[0];
	else
		clip->outside_points[clip->count_outside_point++] = &in->vertex[0];
	if (get_shortest_distance(&in->vertex[1].v, plane) >= 0)
		clip->inside_points[clip->count_inside_point++] = &in->vertex[1];
	else
		clip->outside_points[clip->count_outside_point++] = &in->vertex[1];
	if (get_shortest_distance(&in->vertex[2].v, plane) >= 0)
		clip->inside_points[clip->count_inside_point++] = &in->vertex[2];
	else
		clip->outside_points[clip->count_outside_point++] = &in->vertex[2];
}

void			swap_point(t_clip *clip, t_triangle_raster *in)
{
	if (clip->count_inside_point == 2
		&& clip->inside_points[0] == &in->vertex[0]
		&& clip->inside_points[1] == &in->vertex[2])
	{
		clip->inside_points[0] = &in->vertex[2];
		clip->inside_points[1] = &in->vertex[0];
	}
	if (clip->count_outside_point == 2
		&& clip->outside_points[0] == &in->vertex[0]
		&& clip->outside_points[1] == &in->vertex[2])
	{
		clip->outside_points[0] = &in->vertex[2];
		clip->outside_points[1] = &in->vertex[0];
	}
}

t_u32			triangle_clip_plane(t_plane *plane, t_triangle_raster *in,
	t_triangle_raster out[2])
{
	t_clip	clip;

	clip.count_inside_point = 0;
	clip.count_outside_point = 0;
	plane->n = vec4f_normalize(plane->n);
	check_points(&clip, plane, in);
	swap_point(&clip, in);
	if (clip.count_inside_point == 0)
		return (0);
	else if (clip.count_inside_point == 3)
		out[0] = *in;
	else if (clip.count_inside_point == 1)
		return (one_vertex_inside(&clip, plane, out));
	else
		return (two_vertices_inside(&clip, plane, out));
	return (1);
}
