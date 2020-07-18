/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 11:09:49 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/06 11:09:49 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterizer.h"
#include "mysdl2.h"

static void	lerp_tex_coord(t_triangle_raster *triangle, t_vec3f *w,
		t_fragment_data *data, float z)
{
	data->tex_coord.x = (triangle->vertex[0].v_texture.x * w->x
							+ triangle->vertex[1].v_texture.x * w->y
							+ triangle->vertex[2].v_texture.x * w->z) * z;
	data->tex_coord.y = (triangle->vertex[0].v_texture.y * w->x
							+ triangle->vertex[1].v_texture.y * w->y
							+ triangle->vertex[2].v_texture.y * w->z) * z;
}

static void	set_input_fragment_data(t_triangle_raster *triangle,
		t_vec3f *w, t_fragment_data *data, float z)
{
	lerp_tex_coord(triangle, w, data, z);
}

void		set_color(t_rasterizer *r, t_render_screen *render_screen)
{
	t_fragment_data	data;
	t_context_3d	*context_3d;
	int				index;
	t_vec3f			*w;
	t_camera		*camera;

	camera = render_screen->active_camera;
	w = (t_vec3f *)&r->edges.w.bytes;
	index = r->y * render_screen->surface->w + r->x;
	context_3d = get_context()->context_3d;
	if (context_3d->use_depthbuffer)
	{
		if (r->z >= camera->depth_buffer[index])
			return ;
		camera->depth_buffer[index] = r->z;
	}
	set_input_fragment_data(&r->corr, w, &data, r->z);
	data.material = r->corr.material;
	data.w = *w;
	data.color = r->corr.color;
	data.debug_clip = context_3d->debug_clip;
	fragment_function(&data);
	((t_u32 *)render_screen->surface->pixels)[index] = data.frag_color;
	data.frag_color = 0;
}
