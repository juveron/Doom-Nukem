/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 11:09:46 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/06 11:09:47 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterizer.h"
#include "mysdl2.h"

void		compute_size(t_rasterizer *r, t_tile *tile,
		t_triangle_raster *triangle)
{
	r->x0 = maxi(tile->x_min, floorf(fminf(triangle->vertex[0].v.x,
		fminf(triangle->vertex[1].v.x, triangle->vertex[2].v.x))));
	r->x1 = mini(tile->x_max - 1, floorf(fmaxf(triangle->vertex[0].v.x,
		fmaxf(triangle->vertex[1].v.x, triangle->vertex[2].v.x))));
	r->y = maxi(tile->y_min, floorf(fminf(triangle->vertex[0].v.y,
		fminf(triangle->vertex[1].v.y, triangle->vertex[2].v.y))));
	r->y1 = mini(tile->y_max - 1, floorf(fmaxf(triangle->vertex[0].v.y,
		fmaxf(triangle->vertex[1].v.y, triangle->vertex[2].v.y))));
}

bool		init_raster(t_rasterizer *r, t_tile *tile,
		t_triangle_raster *triangle)
{
	float				area;

	compute_size(r, tile, triangle);
	r->corr = *triangle;
	r->tex.sse = _mm_setr_ps(r->corr.vertex[0].v_texture.z,
			r->corr.vertex[1].v_texture.z, r->corr.vertex[2].v_texture.z, 0);
	if (r->tex.ibytes[0] == 0 && r->tex.ibytes[1] == 0 && r->tex.ibytes[2] == 0)
		return (false);
	area = edge_function(&r->corr.vertex[0].v, &r->corr.vertex[1].v,
			&r->corr.vertex[2].v);
	r->edges = init_edges(r->corr.vertex, &(t_vec4f){r->x0 + 0.5f, r->y + 0.5f,
			0, 1}, area);
	return (true);
}

static void	in_triangle(t_rasterizer *r, t_render_screen *render_screen)
{
	r->tmp.sse = _mm_mul_ps(r->edges.w.sse, r->tex.sse);
	r->z = 1.f / (r->tmp.bytes[0] + r->tmp.bytes[1] + r->tmp.bytes[2]);
	set_color(r, render_screen);
	r->in = true;
}

void		draw_triangle_tile(t_triangle_raster *triangle, t_tile *tile,
		t_render_screen *render_screen)
{
	t_rasterizer		r;

	if (!init_raster(&r, tile, triangle))
		return ;
	while (r.y <= r.y1)
	{
		r.x = r.x0;
		r.in = false;
		while (r.x <= r.x1)
		{
			r.cmp.sse = _mm_cmpge_ps(r.edges.w.sse, _mm_setzero_ps());
			if (r.cmp.ibytes[0] != 0 && r.cmp.ibytes[1] != 0
				&& r.cmp.ibytes[2] != 0)
				in_triangle(&r, render_screen);
			else if (r.in == true)
				break ;
			r.edges.w.sse = _mm_add_ps(r.edges.w.sse, r.edges.step_x.sse);
			++r.x;
		}
		r.edges.w_row.sse = _mm_add_ps(r.edges.w_row.sse, r.edges.step_y.sse);
		r.edges.w = r.edges.w_row;
		++r.y;
	}
}
