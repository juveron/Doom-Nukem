/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_new_sector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:45:15 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 12:46:06 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_existing_wall(t_env *env, t_wall *walls, size_t nb_wall)
{
	size_t	i;

	i = 0;
	while (i < nb_wall - 1)
	{
		draw_line_clip((t_clipping_line){grid_to_win(&walls[i].v1->v.v, env),
			grid_to_win(&walls[i].v2->v.v, env), vec2i(0, 0), vec2i(WIDTH,
			HEIGHT)}, 0xFFFFFF, env->main_window->surface);
		i++;
	}
}

static void	draw_last_wall(t_env *env, t_wall *walls, size_t nb_wall)
{
	if (nb_wall == 1)
	{
		draw_line_clip((t_clipping_line){grid_to_win(&walls[0].v1->v.v, env),
			grid_to_win(&env->editor.position_map.v, env), vec2i(0, 0),
			vec2i(WIDTH, HEIGHT)}, 0xFFFFFF, env->main_window->surface);
		draw_elipse(rect(walls[0].v1->v.v.x * env->editor.zoom
			+ env->editor.offset_z.x, walls[0].v1->v.v.z * env->editor.zoom
			+ env->editor.offset_z.y, 3, 3), 0xFF0000,
			env->main_window->surface);
		return ;
	}
	draw_line_clip((t_clipping_line){grid_to_win(&walls[nb_wall
		- 2].v2->v.v, env), grid_to_win(&env->editor.position_map.v, env),
		vec2i(0, 0), vec2i(WIDTH, HEIGHT)}, 0xFFFFFF,
		env->main_window->surface);
}

static void	draw_point(t_env *env, t_wall *walls, size_t nb_wall)
{
	size_t	i;

	i = 0;
	draw_elipse(rect(walls[0].v1->v.v.x * env->editor.zoom
		+ env->editor.offset_z.x, walls[0].v1->v.v.z * env->editor.zoom
		+ env->editor.offset_z.y, 3, 3), 0xFF0000, env->main_window->surface);
	while (i < nb_wall - 1)
	{
		draw_elipse(rect(walls[i].v2->v.v.x * env->editor.zoom
			+ env->editor.offset_z.x, walls[i].v2->v.v.z * env->editor.zoom
			+ env->editor.offset_z.y, 3, 3), 0xFF0000,
			env->main_window->surface);
		i++;
	}
}

void		draw_new_sector(t_env *env)
{
	t_wall	*walls;
	size_t	nb_wall;

	walls = env->editor.tmp_sector->walls.items;
	nb_wall = env->editor.tmp_sector->walls.total;
	draw_existing_wall(env, walls, nb_wall);
	draw_last_wall(env, walls, nb_wall);
	draw_point(env, walls, nb_wall);
}
