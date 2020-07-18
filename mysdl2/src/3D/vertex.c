/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:54:33 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/11 12:39:58 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"
#include "clipping_internal.h"
#include "rasterizer.h"

void	convert_triangle_to_triangle_raster(t_triangle *triangle,
		t_triangle_raster *raster)
{
	raster->vertex[0].v = *(t_vec4f *)&triangle->vertex[0].v;
	raster->vertex[0].v_texture = *(t_vec3f *)&triangle->vertex[0].v_texture;
	raster->vertex[1].v = *(t_vec4f *)&triangle->vertex[1].v;
	raster->vertex[1].v_texture = *(t_vec3f *)&triangle->vertex[1].v_texture;
	raster->vertex[2].v = *(t_vec4f *)&triangle->vertex[2].v;
	raster->vertex[2].v_texture = *(t_vec3f *)&triangle->vertex[2].v_texture;
}

void	vertex_function(t_triangle *triangle, t_matrix4 *m_mv,
	t_matrix4 *m_p)
{
	t_matrix4			m_mvp;
	t_triangle_raster	tri;
	t_triangle_raster	view;

	matrix_multiply2(m_mv,
		m_p, &m_mvp);
	convert_triangle_to_triangle_raster(triangle, &tri);
	view = tri;
	mul_matrix4_vec4f(&tri.vertex[0].v, &view.vertex[0].v, m_mv);
	mul_matrix4_vec4f(&tri.vertex[1].v, &view.vertex[1].v, m_mv);
	mul_matrix4_vec4f(&tri.vertex[2].v, &view.vertex[2].v, m_mv);
	clip_triangle(&view, m_p);
}

void	process_vertex(t_vertex *vertex, size_t vertex_count,
	t_matrix4 *model_matrix)
{
	t_triangle				triangle;
	size_t					i;
	t_matrix4				m_mv;
	t_context_3d			*context_3d;

	context_3d = get_context()->context_3d;
	matrix_multiply2(model_matrix,
		&context_3d->render_screen.active_camera->m_invert, &m_mv);
	i = 0;
	while (i < vertex_count)
	{
		triangle.vertex[0] = vertex[i + 0];
		triangle.vertex[1] = vertex[i + 1];
		triangle.vertex[2] = vertex[i + 2];
		vertex_function(&triangle, &m_mv,
			&context_3d->render_screen.active_camera->m_proj);
		i += 3;
	}
}
