/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_sector_floor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:03:25 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 16:47:56 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_editor_internal.h"

static void	process_vertex_vector(t_vector *vector, t_matrix4 *invert,
	t_matrix4 *proj)
{
	t_triangle	*triangle;
	size_t		i;

	i = 0;
	triangle = vector->items;
	while (i < vector->total)
	{
		triangle[i].color = 0;
		vertex_function(&triangle[i], invert, proj);
		++i;
	}
}

static void	process_vertex_sector(t_sector *sector)
{
	t_context_3d	*context_3d;
	t_matrix4		*invert;
	t_matrix4		*proj;

	context_3d = get_context()->context_3d;
	invert = &context_3d->render_screen.active_camera->m_invert;
	proj = &context_3d->render_screen.active_camera->m_proj;
	if (sector->has_roof)
	{
		context_3d->material = sector->mtl_ceil;
		process_vertex_vector(&sector->triangle_top, invert, proj);
	}
	context_3d->material = sector->mtl_floor;
	process_vertex_vector(&sector->triangle_bottom, invert, proj);
}

bool		draw_3d_sector_floor(t_sector *sector, t_env *env)
{
	t_context_3d	*context_3d;

	context_3d = get_context()->context_3d;
	if (!context_3d->triangle.items
		&& !vector_init(&context_3d->triangle, sizeof(t_triangle)))
		return (false);
	process_vertex_sector(sector);
	process_vertex_wall(env, sector);
	return (true);
}
