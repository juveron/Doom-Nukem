/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 12:05:42 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/02 12:05:42 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIPPING_INTERNAL_H
# define CLIPPING_INTERNAL_H

# include "draw3d.h"

typedef struct	s_clip
{
	t_vertex_raster	*inside_points[3];
	int				count_inside_point;
	t_vertex_raster	*outside_points[3];
	int				count_outside_point;
}				t_clip;

typedef struct	s_clip_screen_internal
{
	t_triangle_raster	array1[16];
	t_triangle_raster	array2[16];
	t_triangle_raster	*in;
	t_triangle_raster	*out;
	int					n_tri;
	size_t				last_size;
	int					i;
	int					j;
	int					k;
	t_plane				planes[4];
}				t_clip_screen_internal;

t_u32			one_vertex_inside(t_clip *clip, t_plane *plane,
		t_triangle_raster out[2]);
t_u32			two_vertices_inside(t_clip *clip, t_plane *plane,
		t_triangle_raster out[2]);
#endif
