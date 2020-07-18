/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:55:06 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/10 23:54:39 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static bool	draw_3d_sectors(t_env *env)
{
	t_sector	**sector;
	size_t		i;

	sector = env->game->visible_sector.items;
	i = 0;
	while (i < env->game->visible_sector.total)
	{
		draw_3d_sector_floor(sector[i], env);
		++i;
	}
	render_all_triangle();
	return (true);
}

static bool	render(t_env *env)
{
	size_t i;

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
	if (!draw_level(env)
		|| !draw_pickup_object(env, env->ph_context.dt)
		|| !draw_3d_sectors(env))
		return (false);
	if (SDL_BlitSurface(env->framebuffer, NULL, env->main_window->surface,
		&(SDL_Rect){0, 0, WIDTH, HEIGHT}))
		return (false);
	return (true);
}

static bool	render_end_state(t_env *env)
{
	if (env->app_state == APP_GAME_OVER)
	{
		if (env->game_over.animation.bright_ratio > 0.f)
			game_over_animation(env);
		else
		{
			if (!init_game_over_menu(env))
				return (false);
		}
	}
	if (env->app_state == APP_WIN)
		update_win_menu(env);
	return (true);
}

bool		draw_game(void *param)
{
	t_env		*env;

	env = param;
	if (env->game->visible_sector.items == NULL)
		return (false);
	if (env->app_state == APP_GAME && env->gui.status == GUI_NONE)
	{
		if (!render(env))
			return (false);
	}
	else
		env->main_window->force_redraw = env->main_window->need_redraw;
	if ((env->main_window->need_redraw && env->gui.status == GUI_PAUSE)
		|| (env->app_state == APP_GAME_OVER
		&& env->gui.status != GUI_GAME_OVER))
	{
		SDL_BlitSurface(env->framebuffer, NULL, env->main_window->surface,
				&(SDL_Rect){0, 0, WIDTH, HEIGHT});
	}
	if (!hud_off_on(env)
		|| !render_end_state(env))
		return (false);
	return (true);
}
