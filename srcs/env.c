/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 21:19:05 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/12 02:31:49 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_env		*free_env(t_env *env)
{
	size_t	i;

	if (!env)
		return (NULL);
	free_fonts(env);
	free_selection_mode(env);
	destroy_history(&env->editor.history);
	destroy_window(env->main_window);
	free_maps(env);
	mtl_destroy(&env->editor.copy.material);
	if (env->texture_array)
	{
		i = 0;
		while (i < env->texture_array->total)
			destroy_texture(env->texture_array->elem[i++].data);
		map_free(env->texture_array);
	}
	free_image_for_gui(env);
	destroy_sound_manager(&env->sound_manager);
	free(env->map_file.file_name);
	free_all_event(env);
	SDL_FreeSurface(env->framebuffer);
	free(env);
	return (NULL);
}

static void	init_env_p2(t_env *env)
{
	env->editor.zoom = 30;
	env->editor.div = 1;
	env->test_mode = false;
	env->app_state = APP_MAIN_MENU;
	init_shortcuts(&env->shortcuts);
	init_maps(env);
	load_image_for_gui(env);
	env->player.height = PLAYER_HEIGHT;
	env->game_over.active = true;
	env->framebuffer = SDL_ConvertSurface(env->main_window->surface,
			env->main_window->surface->format, 0);
}

t_env		*init_env(void)
{
	t_env	*env;

	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		throw_error("DOOM_NUKEM: malloc fail.", NULL);
	if (!(env->main_window = create_window("Main window",
		vec2i(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED),
		vec2i(WIDTH, HEIGHT), 0)))
		throw_error("DOOM_NUKEN: Fail to create window.", env);
	if (!init_fonts(env))
		throw_error("DOOM_NULEM: Fail to load fonts.", env);
	if (!change_selection_mode(env, EDITOR_SELECT_POINT))
		throw_error("DOOM_NULEM: Fail to create selection mode surface.", env);
	if (!(env->texture_array = map_init(sizeof(t_texture *))))
		throw_error("DOOM_NULEM: Fail to init texture array.", env);
	if (!init_event_handler(&env->editor.event_handler))
		throw_error("Event_handler initialization failed.", env);
	if (!init_sound_manager(&env->sound_manager))
		throw_error("Sound_manager initialization failed.", env);
	init_env_p2(env);
	return (env);
}
