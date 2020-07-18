/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_game_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 09:45:38 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/06 16:13:47 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	init_game_audio(t_env *env)
{
	if (env->current_map->level.start.available)
		if (!set_source_position(env->sound_manager.audio_objects.
				start_of_level.source, env->current_map->level.start.position)
			|| !change_source_state(env->sound_manager.
				audio_objects.start_of_level.source, SRC_PLAY))
			return (false);
	if (env->current_map->level.end.available)
		if (!set_source_position(env->sound_manager.audio_objects.
				end_of_level.source, env->current_map->level.end.position)
			|| !change_source_state(env->sound_manager.
				audio_objects.end_of_level.source, SRC_PLAY))
			return (false);
	if (!change_source_state(env->sound_manager.audio_ambient.
		ambient_music.source, SRC_PLAY))
		return (false);
	return (true);
}

bool	init_editor_game_state(t_env *env)
{
	env->app_state = APP_EDITOR_GAME;
	if (!init_game_audio(env)
		|| !init_object_manager(env)
		|| !init_remaining_object(env)
		|| !init_levels_manager_3d(env))
		return (false);
	return (true);
}
