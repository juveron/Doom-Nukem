/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:38:31 by thboura           #+#    #+#             */
/*   Updated: 2020/07/12 03:23:14 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		destroy_other_options(t_other_options *other)
{
	int	ret;

	ret = 0;
	if (!other)
		return (false);
	ret += !destroy_check_box(&other->game_over_animation_check_box);
	ret += !destroy_label(&other->game_over_animation_label);
	ret += !destroy_check_box(&other->fps_check_box);
	ret += !destroy_label(&other->fps_label);
	ret += !destroy_check_box(&other->debug_triangles_check_box);
	ret += !destroy_label(&other->debug_triangles_label);
	ret += !destroy_check_box(&other->skybox_check_box);
	ret += !destroy_label(&other->skybox_label);
	ret += !destroy_container(&other->container);
	return (ret == 0);
}

bool		create_other_options(t_env *env, t_other_options *other)
{
	SDL_Rect	option_template;
	size_t		num_of_options;

	num_of_options = 8;
	option_template.w = env->main_window->size.x / 8;
	option_template.h = (env->main_window->size.y - 50) / num_of_options;
	option_template.x = env->main_window->size.x - (option_template.w / 2
		+ (50 / 2) + 150);
	option_template.y = (env->main_window->size.y - 50) % num_of_options;
	if (!(other->container = create_container((SDL_Rect){0, 50,
		env->main_window->size.x, env->main_window->size.y - 50}, true,
		0X777777FF)))
		return (false);
	if (!(other->skybox_label = create_label(vec2i(25,
			0 * option_template.h + option_template.y + (option_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(other->skybox_label, "Skybox")
		|| !container_add(other->container, other->skybox_label))
		return (destroy_other_options(other));
	return (create_other_options_p2(env, other, option_template));
}

bool		init_other_options(void *param)
{
	t_env	*env;

	env = param;
	if (env->gui.settings_menu.current_option != OTHER_OPTION)
	{
		env->gui.settings_menu.other_button->component.background = 0X777777FF;
		env->gui.settings_menu.other_button->component.need_redraw = true;
		disable_current_option(&env->gui.settings_menu);
	}
	env->gui.settings_menu.current_option = OTHER_OPTION;
	verify_other_check_boxes(env, &env->gui.settings_menu.other);
	env->gui.settings_menu.other.container->component.is_visible = true;
	return (true);
}
