/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_p3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 10:19:51 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/14 10:29:38 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		destroy_menu(t_env *env)
{
	int	ret;

	ret = 0;
	env->gui.status = GUI_NONE;
	ret += !destroy_game_over_menu(&env->gui.game_over_menu);
	ret += !destroy_win_menu(&env->gui.win_menu);
	ret += !destroy_settings_menu(&env->gui.settings_menu);
	ret += !destroy_pause_menu(&env->gui.pause_menu);
	ret += !destroy_game_pause(&env->gui.game_pause_menu);
	ret += !destroy_level_menu(&env->gui.levels_menu);
	ret += !destroy_sector_menu(&env->gui.sector_menu);
	ret += !destroy_select_texture_menu(env->gui.texture_menu);
	ret += !destroy_texture_menu(&env->gui.material_menu);
	ret += !destroy_custom_window(&env->gui.window);
	return (ret == 0);
}

static bool	return_and_destroy_menu(t_env *env)
{
	destroy_menu(env);
	return (false);
}

static bool	on_close(void *target, void *param)
{
	t_env *env;

	env = param;
	(void)target;
	env->gui.status = GUI_NONE;
	return (true);
}

bool		init_menu(t_env *env)
{
	if (!(env->gui.window = create_custom_window(rect(WIDTH / 2, 0, 600, 700),
			0x333333FF))
		|| !add_custom_action(env->gui.window->on_window_close,
			&(t_custom_event){on_close, env}))
		return (false);
	custom_window_set_draggable(env->gui.window, true);
	set_visible(&env->gui.window->component, false);
	if (!container_add(env->main_window->main_container, env->gui.window)
		|| !(env->gui.material_menu = create_texture_menu(&env->gui.window->
			container->component, env))
		|| !(env->gui.texture_menu = create_selec_texture_menu(env)))
		return (return_and_destroy_menu(env));
	set_visible(&env->gui.texture_menu->window->component, false);
	if (!create_sector_menu(&env->gui.sector_menu, env)
		|| !create_levels_menu(&env->gui.levels_menu, env)
		|| !create_pause_menu(env, &env->gui.pause_menu)
		|| !create_game_pause_menu(env, &env->gui.game_pause_menu)
		|| !create_settings_menu(env, &env->gui.settings_menu)
		|| !create_game_over_menu(env, &env->gui.game_over_menu)
		|| !create_win_menu(env, &env->gui.win_menu))
		return (return_and_destroy_menu(env));
	return (true);
}
