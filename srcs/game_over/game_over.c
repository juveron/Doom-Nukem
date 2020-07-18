/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 18:28:01 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 13:10:50 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_color	set_brightness(t_color color, float x)
{
	return (((int)((color & 0xFF0000) * x) & 0xFF0000) | ((int)((color
		& 0x00FF00) * x) & 0x00FF00) | ((int)((color & 0x0000FF) * x)
		& 0x0000FF));
}

void	game_over_animation(t_env *env)
{
	t_u32	*pxl;
	int		x;
	int		y;

	if (env->game_over.animation.bright_ratio <= 0.f)
		return ;
	pxl = (t_u32 *)env->main_window->surface->pixels;
	y = 0;
	while (y < env->main_window->surface->h)
	{
		x = 0;
		while (x < env->main_window->surface->w)
		{
			pxl[x + y * env->main_window->surface->w] = set_brightness(
				pxl[x + y * env->main_window->surface->w],
				env->game_over.animation.bright_ratio);
			x++;
		}
		y++;
	}
	env->game_over.animation.bright_ratio = 1.f - (float)clock_get_microseconds(
		&env->game_over.animation.time) / 1000000.f
		/ get_buffer_duration_in_seconds(env->sound_manager.master->library->
		sounds_list->elem[GAME_OVER_MUSIC].data);
	env->main_window->force_redraw = true;
}

bool	init_game_over_menu(t_env *env)
{
	clock_pause(&env->game_over.animation.time);
	SDL_SetRelativeMouseMode(false);
	init_game_over_gui_menu(env);
	return (true);
}

bool	start_game_over_animation(t_env *env)
{
	env->game_over.animation.bright_ratio = 1.f;
	clock_restart(&env->game_over.animation.time);
	if (!change_source_state(env->sound_manager.audio_ambient.game_over_music.
		source, SRC_PLAY))
		return (false);
	return (true);
}

bool	init_game_over(t_env *env)
{
	env->app_state = APP_GAME_OVER;
	clock_pause(&env->hud.time);
	if (!change_all_sources_state(&env->sound_manager, SRC_STOP))
		return (false);
	return (true);
}
