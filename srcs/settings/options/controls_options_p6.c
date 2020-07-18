/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_options_p6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:40:38 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 18:42:17 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		destroy_input_display(t_env *env, t_input_display *display)
{
	int	ret;

	ret = 0;
	if (!display)
		return (false);
	ret += !destroy_label(&display->label);
	ret += !destroy_container(&display->container);
	env->main_window->main_container->component.need_redraw = true;
	return (ret == 0);
}

bool		create_input_display(t_env *env, t_input_display *display)
{
	if (!(display->container = create_container((SDL_Rect){0, 0,
		env->main_window->size.x, env->main_window->size.y}, true, 0x00000077)))
		return (false);
	if (!(display->label = create_label(vec2i(env->main_window->size.x / 2
			- 110 / 2, env->main_window->size.y / 2), 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(display->label, "Press a key")
		|| !container_add(display->container, &display->label->component))
		return (destroy_input_display(env, display));
	if (!container_add(env->main_window->main_container,
		&display->container->component))
		return (destroy_input_display(env, display));
	display->container->component.is_visible = false;
	return (true);
}

static void	gui_init_input(t_gui *gui, void *set_input_func)
{
	gui->input_handler.previous_state = gui->status;
	gui->status = GUI_INPUT;
	gui->input_handler.set_input_func = set_input_func;
	gui->input_handler.display.container->component.is_visible = true;
}

bool		init_input_event(void *env, void *set_input_func)
{
	t_env	*tmp_env;

	tmp_env = (t_env *)env;
	if (!create_input_display(tmp_env, &tmp_env->gui.input_handler.display))
		return (false);
	gui_init_input(&tmp_env->gui, set_input_func);
	tmp_env->main_window->main_container->component.need_redraw = true;
	return (true);
}
