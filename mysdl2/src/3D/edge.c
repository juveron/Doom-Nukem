/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:04:11 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 22:10:57 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

inline t_edges	init_edges(t_vertex_raster *vertices, t_vec4f *vec, float area)
{
	t_edges	edges;

	edges.step_x.sse = _mm_setr_ps((vertices[2].v.y - vertices[1].v.y) / area,
		(vertices[0].v.y - vertices[2].v.y) / area,
		(vertices[1].v.y - vertices[0].v.y) / area, 1);
	edges.step_y.sse = _mm_setr_ps((vertices[1].v.x - vertices[2].v.x) / area,
		(vertices[2].v.x - vertices[0].v.x) / area,
		(vertices[0].v.x - vertices[1].v.x) / area, 1);
	edges.w_row.sse = _mm_setr_ps(((vec->x - vertices[1].v.x) * (vertices[2].v.y
		- vertices[1].v.y) - (vec->y - vertices[1].v.y) * (vertices[2].v.x
		- vertices[1].v.x)) / area, ((vec->x - vertices[2].v.x)
		* (vertices[0].v.y - vertices[2].v.y) - (vec->y - vertices[2].v.y)
		* (vertices[0].v.x - vertices[2].v.x)) / area, ((vec->x
		- vertices[0].v.x) * (vertices[1].v.y - vertices[0].v.y) - (vec->y
		- vertices[0].v.y) * (vertices[1].v.x - vertices[0].v.x)) / area, 1);
	edges.w = edges.w_row;
	return (edges);
}
