/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juv <juv@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 19:56:14 by thboura           #+#    #+#             */
/*   Updated: 2020/06/26 13:21:15 by juv              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static SDL_Rect	comment_rect(t_env *env, t_vec3f position, bool start)
{
	if (start)
		return (rect(position.x * env->editor.zoom + env->editor.offset_z.x
			- env->levels_manager.start_surface->w / 2,
			position.z * env->editor.zoom + env->editor.offset_z.y + 10, 0, 0));
	else
		return (rect(position.x * env->editor.zoom + env->editor.offset_z.x
			- env->levels_manager.end_surface->w / 2,
			position.z * env->editor.zoom + env->editor.offset_z.y + 10, 0, 0));
}

static void		draw_start_point(t_vec3f position, int size, t_env *env)
{
	t_clipping_line	line;
	t_vec2i			pos;
	t_vec2f			angle;

	pos = vec2i(position.x * env->editor.zoom + env->editor.offset_z.x,
				position.z * env->editor.zoom + env->editor.offset_z.y);
	draw_elipse(rect(pos.x, pos.y, size, size),
			0xFF00FF, env->main_window->surface);
	blit_surface(env->levels_manager.start_surface, comment_rect(env, position,
		true), env->main_window);
	line.bound_min = vec2i(0, 0);
	line.bound_max = vec2i(WIDTH, HEIGHT);
	line.v0 = pos;
	angle = vec2f_mul(vec2f_from_angle(radian(env->current_map->level.start.
			rotation)), 20);
	line.v1 = vec2i(angle.y + pos.x, -angle.x + pos.y);
	draw_line_clip(line, 0x00FF00FF, env->main_window->surface);
}

static void		draw_end_point(t_vec3f position, int size, t_env *env)
{
	t_vec2i			pos;

	pos = vec2i(position.x * env->editor.zoom + env->editor.offset_z.x,
			position.z * env->editor.zoom + env->editor.offset_z.y);
	draw_elipse(rect(pos.x, pos.y, size, size),
			0xFFFF00, env->main_window->surface);
	blit_surface(env->levels_manager.end_surface, comment_rect(env, position,
		false), env->main_window);
}

void			draw_gui_level(t_env *env)
{
	if (env->current_map->level.start.available)
		draw_start_point(env->current_map->level.start.position, 6, env);
	if (env->current_map->level.end.available)
		draw_end_point(env->current_map->level.end.position, 6, env);
}
