/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_editor_p2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:38:45 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/04 17:52:15 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	add_vertex_internal(t_triangle *triangle, size_t start_index,
	t_matrix4 *invert, t_matrix4 *proj)
{
	vertex_function(&triangle[start_index], invert, proj);
	vertex_function(&triangle[start_index + 1], invert, proj);
}

static void	process_neighbor(t_wall *wall, t_context_3d *context_3d,
	t_matrix4 *invert, t_matrix4 *proj)
{
	if (wall->wall_location & WALL_TOP)
	{
		context_3d->material = wall->mtl_top;
		add_vertex_internal(wall->triangle, 0, invert, proj);
	}
	if (wall->wall_location & WALL_BOTTOM)
	{
		context_3d->material = wall->mtl_bottom;
		add_vertex_internal(wall->triangle, 2, invert, proj);
	}
}

void		process_vertex_wall(t_env *env, t_sector *sector)
{
	size_t					i;
	t_wall					*walls;
	t_context_3d			*context_3d;
	t_matrix4				*invert;
	t_matrix4				*proj;

	(void)env;
	context_3d = get_context()->context_3d;
	invert = &context_3d->render_screen.active_camera->m_invert;
	proj = &context_3d->render_screen.active_camera->m_proj;
	walls = sector->walls.items;
	i = 0;
	while (i < sector->walls.total)
	{
		if (walls[i].neighbor == NULL)
		{
			context_3d->material = walls[i].mtl_top;
			add_vertex_internal(walls[i].triangle, 0, invert, proj);
		}
		else
			process_neighbor(&walls[i], context_3d, invert, proj);
		i++;
	}
}
