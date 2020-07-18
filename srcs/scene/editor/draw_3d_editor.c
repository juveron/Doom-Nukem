/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_editor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:38:45 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 17:05:44 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_editor_internal.h"

static bool	render_p2(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->current_map->sectors->total)
	{
		if (!draw_3d_sector_floor(*(t_sector **)map_get_index(env->current_map->
			sectors, i), env))
			return (false);
		++i;
	}
	render_all_triangle();
	return (true);
}

static bool	render(t_env *env)
{
	size_t	i;

	i = 0;
	env->main_window->force_redraw = true;
	while (i < HEIGHT * WIDTH)
		env->camera.depth_buffer[i++] = 1000.f;
	update_camera(&env->camera);
	if (env->sky_enable)
	{
		env->skybox->transform.position = env->camera.transform.position;
		env->skybox->transform.rotation.y += env->ph_context.dt * 1
			* env->time_scale;
		enable_depthbuffer(false);
		force_draw_render_object(env->skybox);
		enable_depthbuffer(true);
	}
	else
		ft_bzero(env->framebuffer->pixels, env->framebuffer->h
			* env->framebuffer->pitch);
	if (!draw_level(env)
		|| !draw_pickup_object(env, env->ph_context.dt))
		return (false);
	return (render_p2(env));
}

bool		draw_3d_mode(t_env *env)
{
	if (env->app_state == APP_EDITOR_GAME && env->gui.status != GUI_PAUSE
		&& env->gui.status != GUI_SETTINGS)
	{
		ft_memset(env->main_window->surface->pixels, 0,
			env->main_window->surface->h * env->main_window->surface->pitch);
		if (!render(env))
			return (false);
		SDL_BlitSurface(env->framebuffer, NULL, env->main_window->surface,
				&(SDL_Rect){0, 0, WIDTH, HEIGHT});
	}
	else if (env->main_window->need_redraw)
	{
		if (env->gui.status == GUI_PAUSE)
			SDL_BlitSurface(env->framebuffer, NULL, env->main_window->surface,
					&(SDL_Rect){0, 0, WIDTH, HEIGHT});
		env->main_window->force_redraw = true;
	}
	return (true);
}
