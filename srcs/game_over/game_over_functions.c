/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 15:35:40 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 17:26:27 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	resume_game_over_menu(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->gui.status = GUI_NONE;
	env->gui.game_over_menu.container->component.is_visible = false;
	env->main_window->main_container->component.need_redraw = true;
	return (set_game_start(env));
}

bool	main_menu_game_over_menu(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->time_scale = 1.f;
	load_scene(env->scenes.main_menu);
	return (true);
}

bool	exit_game_over_menu(void *param)
{
	(void)param;
	get_context()->run = false;
	return (true);
}
