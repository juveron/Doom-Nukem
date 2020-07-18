/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:58:47 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/30 14:20:12 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"
#include "draw3d.h"

inline float	edge_function(t_vec4f *a, t_vec4f *b, t_vec4f *c)
{
	return ((c->x - a->x) * (b->y - a->y) - (c->y - a->y) * (b->x - a->x));
}

void			get_mv(t_matrix4 *m_mesh, t_camera *camera, t_matrix4 *out)
{
	*out = matrix_multiply(m_mesh, &camera->m_invert);
}

bool			force_draw_render_object(t_render_object *obj)
{
	t_context_3d	*context_3d;

	update_transform(&obj->transform);
	context_3d = get_context()->context_3d;
	if (!context_3d->triangle.items
		&& !vector_init(&context_3d->triangle, sizeof(t_triangle)))
		return (false);
	if (obj->has_custom_material)
		context_3d->material = obj->custom_material;
	else
		context_3d->material = obj->mesh->default_material;
	process_vertex(obj->mesh->vertex.items, obj->mesh->vertex.total,
		&obj->transform.rot_pos_scale);
	active_worker();
	worker_wait();
	vector_free(&context_3d->triangle);
	return (true);
}

bool			draw_render_object(t_render_object *obj)
{
	t_context_3d	*context_3d;

	update_transform(&obj->transform);
	context_3d = get_context()->context_3d;
	if (!context_3d->triangle.items
		&& !vector_init(&context_3d->triangle, sizeof(t_triangle)))
		return (false);
	if (obj->has_custom_material)
		context_3d->material = obj->custom_material;
	else
		context_3d->material = obj->mesh->default_material;
	process_vertex(obj->mesh->vertex.items, obj->mesh->vertex.total,
		&obj->transform.rot_pos_scale);
	return (true);
}

void			render_all_triangle(void)
{
	t_context_3d	*context_3d;

	context_3d = get_context()->context_3d;
	active_worker();
	worker_wait();
	vector_free(&context_3d->triangle);
}
