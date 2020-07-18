/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 15:43:39 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/15 02:15:58 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_manager.h"
#include "render.h"
#include "game.h"
#include "inputs.h"

bool	set_game_start(t_env *env)
{
	if (!change_all_sources_state(&env->sound_manager, SRC_REWIND))
		return (false);
	if (!init_game_audio(env))
		return (false);
	SDL_SetRelativeMouseMode(true);
	load_level_position(env);
	teleport_to_spawn(env);
	free_remaining_objects(env);
	init_remaining_object(env);
	env->app_state = APP_GAME;
	env->gui.status = GUI_NONE;
	init_hud(env);
	clock_set_milliseconds(&env->hud.time, env->game->current_segment_time);
	return (true);
}

bool	init_game(void *param)
{
	t_env	*env;

	env = param;
	env->current_map = *(t_doom_map **)vector_get(&env->maps, 0);
	if (!(env->game = create_game_struct()))
		return (false);
	init_game_struct(env->game);
	if (!create_hud(env))
		return (false);
	if (!init_menu(env)
		|| !init_object_manager(env)
		|| !init_remaining_object(env)
		|| !init_levels_manager_3d(env))
		return (false);
	env->use_gravity = true;
	compute_all_pvs(env);
	if (!set_game_start(env))
		return (false);
	return (true);
}

bool	destroy_game(void *param)
{
	t_env	*env;

	env = param;
	free_remaining_objects(env);
	destroy_object_manager(env);
	free_levels_manager_3d(env);
	destroy_game_struct(&env->game);
	SDL_SetRelativeMouseMode(false);
	destroy_menu(env);
	destroy_hud(env);
	return (true);
}

t_scene	*create_game_scene(t_env *env)
{
	t_scene	*game_scene;

	if (!(game_scene = create_scene(init_game, draw_game, update_game,
		destroy_game)))
		return (NULL);
	add_param_to_scene(game_scene, env);
	return (game_scene);
}
