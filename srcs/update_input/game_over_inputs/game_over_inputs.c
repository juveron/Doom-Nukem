/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over_inputs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:20:52 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 15:05:49 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	game_over_inputs(t_env *env)
{
	if (get_key_down(env->shortcuts.game_over.skip_animation))
	{
		env->game_over.animation.bright_ratio = 0.f;
		if (!change_source_state(env->sound_manager.audio_ambient.
			game_over_music.source, SRC_STOP))
			return (false);
	}
	return (true);
}
