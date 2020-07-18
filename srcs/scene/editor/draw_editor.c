/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:35:41 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 16:16:32 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_editor_internal.h"

static bool	draw_pvs(t_env *env)
{
	t_sector	*sector;
	t_vec2i		mouse_pos;
	t_vec2f		map_pos;

	if (get_key(SDL_SCANCODE_K))
	{
		mouse_pos = get_mouse_position();
		map_pos = win_to_map(&mouse_pos, env);
		if ((sector = is_in_sector(env, &map_pos, true)))
		{
			if (!show_pvs(sector, env))
				return (false);
		}
	}
	return (true);
}

static bool	draw_2d_mode(t_env *env)
{
	if (env->need_redraw || env->main_window->need_redraw)
	{
		env->main_window->force_redraw = true;
		ft_memset(env->main_window->surface->pixels, 0,
			env->main_window->surface->h * env->main_window->surface->pitch);
		draw_grid(env);
		draw_sectors(env);
		draw_gui_level(env);
		draw_pickup_object_editor(env);
		draw_snap_point(env);
		if (env->editor.state.global_state == EDITOR_MAKE_SECTOR)
			draw_new_sector(env);
		if (DEBUG_SELECTION_STATE)
		{
			print_global_state_debug(env);
			print_point_selected_debug(env);
		}
		if (!draw_pvs(env))
			return (false);
	}
	draw_notify(env);
	return (true);
}

bool		draw_editor(void *param)
{
	t_env *env;

	env = param;
	if (env->editor.history.available && env->editor.history.
		window->need_redraw)
	{
		env->need_redraw = true;
		env->editor.history.window->force_redraw = true;
	}
	if (env->app_state == APP_EDITOR)
		draw_2d_mode(env);
	else
		draw_3d_mode(env);
	env->need_redraw = false;
	return (true);
}
