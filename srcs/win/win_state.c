/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:31:12 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 16:31:13 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	init_win_state(t_env *env)
{
	env->app_state = APP_WIN;
	clock_pause(&env->hud.time);
	if (!change_all_sources_state(&env->sound_manager, SRC_STOP))
		return (false);
	return (true);
}

bool	init_win_menu(t_env *env)
{
	SDL_SetRelativeMouseMode(false);
	if (!init_win_gui_menu(env))
		return (false);
	return (true);
}
