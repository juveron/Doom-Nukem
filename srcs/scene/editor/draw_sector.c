/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:46:56 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/09 22:38:05 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_triangle2(t_triangle *triangle, t_env *env)
{
	t_vec2i		pos0;
	t_vec2i		pos1;
	t_vec2i		pos2;

	pos0 = grid_to_win(&triangle->vertex[0].v, env);
	pos1 = grid_to_win(&triangle->vertex[1].v, env);
	pos2 = grid_to_win(&triangle->vertex[2].v, env);
	draw_line_clip((t_clipping_line){pos0, pos1, vec2i(0, 0),
		vec2i(WIDTH, HEIGHT)}, 0x3dc5ff, env->main_window->surface);
	draw_line_clip((t_clipping_line){pos1, pos2, vec2i(0, 0),
		vec2i(WIDTH, HEIGHT)}, 0x3dc5ff, env->main_window->surface);
	draw_line_clip((t_clipping_line){pos2, pos0, vec2i(0, 0),
		vec2i(WIDTH, HEIGHT)}, 0x3dc5ff, env->main_window->surface);
}

static void	draw_wall(t_wall *wall, t_env *env)
{
	t_color	color;
	t_vec2i	tmp;

	color = 0xFFFFFF;
	if (wall == env->editor.closest)
		color = 0x00FF00;
	else if (wall->neighbor != NULL)
		color = 0xFF0000;
	tmp = grid_to_win(&wall->v1->v.v, env);
	draw_line_clip((t_clipping_line){tmp, grid_to_win(&wall->v2->v.v, env),
		vec2i(0, 0), vec2i(WIDTH, HEIGHT)}, color, env->main_window->surface);
	draw_elipse((SDL_Rect){tmp.x, tmp.y, 3, 3}, 0xFF0000,
		env->main_window->surface);
}

static void	draw_sector(t_sector *sector, t_env *env)
{
	size_t		i;
	t_triangle	*triangle;
	size_t		nb_triangle;
	t_wall		*walls;
	size_t		nb_wall;

	i = 0;
	triangle = sector->triangle_bottom.items;
	nb_triangle = sector->triangle_bottom.total;
	while (i < nb_triangle)
	{
		draw_triangle2(&triangle[i], env);
		++i;
	}
	i = 0;
	walls = sector->walls.items;
	nb_wall = sector->walls.total;
	while (i < nb_wall)
	{
		draw_wall(&walls[i], env);
		++i;
	}
}

void		draw_sectors(t_env *env)
{
	size_t	i;
	size_t	nb_sector;
	t_map	*sectors;

	sectors = env->current_map->sectors;
	nb_sector = env->current_map->sectors->total;
	i = 0;
	while (i < nb_sector)
	{
		draw_sector(*(t_sector **)map_get_index(sectors, i), env);
		i++;
	}
}
