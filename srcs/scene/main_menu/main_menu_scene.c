/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 12:01:29 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/13 02:01:00 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_manager.h"
#include "doom_nukem.h"

bool	init_main_menu(void *param)
{
	t_env	*env;

	env = param;
	if (!create_settings_menu(env, &env->gui.settings_menu))
		return (false);
	if (!create_gui_main_menu(&env->gui.main_menu, env))
		return (false);
	env->gui.status = GUI_MAIN_MENU;
	env->app_state = APP_MAIN_MENU;
	return (true);
}

bool	draw_main_menu(void *param)
{
	t_env		*env;
	t_vec2ui	pos;
	t_color		color;
	t_u32		*pixels;
	float		t;

	env = param;
	pixels = env->main_window->surface->pixels;
	pos.x = 0;
	while (pos.x < WIDTH)
	{
		pos.y = 0;
		t = fabsf(sinf(pos.x * 0.001 + env->ph_context.current_time));
		color = lerpi(0x00, 0xFF, t) << 16;
		color |= lerpi(0x00, 0xFF, 1.0 - t);
		while (pos.y < HEIGHT)
		{
			pixels[pos.x + pos.y * WIDTH] = color;
			++pos.y;
		}
		++pos.x;
	}
	env->main_window->force_redraw = true;
	return (true);
}

bool	update_main_menu(void *param)
{
	t_env	*env;

	env = param;
	if (!ph_loop(&env->ph_context))
		return (false);
	if (!update_input(env))
		return (false);
	return (true);
}

bool	destroy_main_menu(void *param)
{
	t_env *env;

	env = param;
	destroy_gui_main_menu(&env->gui.main_menu);
	destroy_settings_menu(&env->gui.settings_menu);
	return (true);
}

t_scene	*create_main_menu_scene(t_env *env)
{
	t_scene	*main_menu;

	if (!(main_menu = create_scene(init_main_menu, draw_main_menu,
		update_main_menu, destroy_main_menu)))
		return (NULL);
	add_param_to_scene(main_menu, env);
	return (main_menu);
}
